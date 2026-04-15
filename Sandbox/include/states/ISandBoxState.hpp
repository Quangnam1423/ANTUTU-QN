#ifndef ISANDBOX_STATE_HPP
#define ISANDBOX_STATE_HPP

/// @brief Different states of the sandbox.
enum class SandBoxState
{
    NONE = 0,
    INITIALIZED,
    RUNNING,
    PAUSED,
    STOPPED,
    TERMINATED
};

/// @brief Different types of sandbox states.
enum class SandBoxStateType
{
    INTRODUCE = 0,
    MAIN_MENU,
    SETTINGS,
    GAMEPLAY,
    PAUSE_MENU,
    GAME_OVER
};

/// @brief Interface for sandbox states.
class ISandBoxState
{
    virtual ~ISandBoxState() = default;
    virtual void Init() = 0;
    virtual void Cleanup() = 0;
    //virtual void HandleEvent(Button& button) = 0;
    virtual void Update(float deltaTime) = 0;
    virtual void Render() = 0;
    virtual void Pause() = 0;
    virtual void Resume() = 0;
    virtual void Exit() = 0;
    virtual bool IsFinished() const = 0;
};

#endif // ISANDBOX_STATE_HPP