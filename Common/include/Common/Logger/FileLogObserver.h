#ifndef FILE_LOG_OBSERVER_H
#define FILE_LOG_OBSERVER_H

#include <Common/Logger/ILogObserver.h>
#include <fstream>
#include <filesystem>
#include <string>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>

#define MAX_FILE_SIZE 10 * 1024 * 1024 // 10 MB
#define MAX_BACKUP_FILES 10

namespace fs = std::filesystem;

namespace Common
{
	class COMMON_API FileLogObserver : public ILogObserver
	{
	public:
		FileLogObserver(const fs::path& filepath, 
			size_t maxFileSize = MAX_FILE_SIZE,
			size_t maxBackupFiles = MAX_BACKUP_FILES);
		virtual ~FileLogObserver();
		void OnLogReceived(const std::string& message) override;
	private:
		void ProcessLogQueue();
		void RotateFiles();
		size_t GetInitialFileSize();
	private:
		std::queue<std::string> m_logQueue;
		std::mutex m_queueMutex;
		std::condition_variable m_queueCV;
		std::thread m_workerThread;
		std::atomic<bool> m_running;

		fs::path m_filepath;
		std::ofstream m_logFile;

		size_t m_maxFileSize;
		size_t m_maxBackupFiles;
		size_t m_currentFileSize;
	};
}

#endif // FILE_LOG_OBSERVER_H