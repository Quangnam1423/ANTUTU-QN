#include <Common/Logger/FileLogObserver.h>

namespace Common
{
	FileLogObserver::FileLogObserver(const fs::path& filepath,
		size_t maxFileSize,
		size_t maxBackupFiles)
		: m_running(true)
		, m_maxFileSize(maxFileSize)
		, m_maxBackupFiles(maxBackupFiles)
		, m_filepath(filepath)
	{
		fs::path parentDir = m_filepath.parent_path();
		if (!parentDir.empty() && !fs::exists(parentDir))
		{
			std::error_code ec;
			fs::create_directories(parentDir, ec);
			if (ec)
			{
				throw std::runtime_error(
					"Failed to create log directory: "
					+ parentDir.string()
					+ ", error: "
					+ ec.message()
				);
			}
		}
		m_logFile.open(m_filepath, std::ios::app | std::ios::binary);
		if (!m_logFile.is_open())
		{
			throw std::runtime_error("Failed to open log file: " + m_filepath.string());
		}
		else
		{
			m_currentFileSize = GetInitialFileSize();
			m_workerThread = std::thread(&FileLogObserver::ProcessLogQueue, this);
		}
	}

	FileLogObserver::~FileLogObserver()
	{
		m_running = false;
		m_queueCV.notify_all();
		if (m_workerThread.joinable())
		{
			m_workerThread.join();
		}
		if (m_logFile.is_open())
		{
			m_logFile.close();
		}
	}

	void FileLogObserver::OnLogReceived(const std::string& message)
	{
		{
			std::lock_guard<std::mutex> lock(m_queueMutex);
			m_logQueue.push(message);
		}
		m_queueCV.notify_all();
	}

	void FileLogObserver::ProcessLogQueue()
	{
		while (m_running || !m_logQueue.empty())
		{
			std::queue<std::string> localQueue;
			{
				std::unique_lock<std::mutex> lock(m_queueMutex);
				m_queueCV.wait(lock, [this]() { 
					return !m_logQueue.empty() || !m_running; 
				});
				std::swap(localQueue, m_logQueue);
			}
			
			if (!localQueue.empty())
			{
				if (!m_logFile.is_open())
				{
					m_logFile.open(m_filepath, std::ios::app);
					if (!m_logFile.is_open())
					{
						throw std::runtime_error("Failed to open log file: " + m_filepath.string());
					}
				}

				if (m_logFile.is_open())
				{
					while (!localQueue.empty())
					{
						const std::string& message = localQueue.front();
						size_t messageSize = message.length() + 1;

						if (m_currentFileSize + messageSize > m_maxFileSize)
						{
							RotateFiles();
						}

						m_logFile << message;
						m_currentFileSize += messageSize;

						localQueue.pop();
					}
					m_logFile.flush();
				}
				else
				{
					while (!localQueue.empty())
					{
						localQueue.pop();
					}
				}
			}
		}
	}

	void FileLogObserver::RotateFiles()
	{
		if (m_logFile.is_open())
		{
			m_logFile.close();
		}

		for (size_t i = m_maxBackupFiles; i > 0; --i)
		{
			fs::path src = m_filepath;
			if (i != 1)
			{
				src += "." + std::to_string(i - 1);
			}
			fs::path dest = m_filepath;
			dest += "." + std::to_string(i);

			std::error_code ec;
			if (fs::exists(src, ec))
			{
				if (fs::exists(dest, ec))
				{
					fs::remove(dest, ec);
				}
				fs::rename(src, dest, ec);
			}
		}

		m_logFile.open(m_filepath, std::ios::trunc | std::ios::binary);
		if (!m_logFile.is_open())
		{
			throw std::runtime_error("Failed to open log file: " + m_filepath.string());
		}
		m_currentFileSize = 0;
	}

	size_t FileLogObserver::GetInitialFileSize()
	{
		std::error_code ec;
		if (fs::exists(m_filepath, ec))
		{
			return fs::file_size(m_filepath, ec);
		}
		return 0;
	}
}