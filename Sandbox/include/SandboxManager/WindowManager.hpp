#ifndef SANDBOX_WINDOW_MANAGER_HPP
#define SANDBOX_WINDOW_MANAGER_HPP

namespace SB
{
    class WindowManager
    {
    public:
        WindowManager();
        ~WindowManager();

        WindowManager(const WindowManager&) = delete;                                 // delete copy constructor
        WindowManager& operator=(const WindowManager&) = delete;                      // delete copy assignment
        WindowManager(WindowManager&&) = delete;                                      // delete move constructor
        WindowManager& operator=(WindowManager&&) = delete;                           // delete move assignment

    private:
        // Private members for managing windows will go here in the future
    };
}


#endif // SANDBOX_WINDOW_MANAGER_HPP