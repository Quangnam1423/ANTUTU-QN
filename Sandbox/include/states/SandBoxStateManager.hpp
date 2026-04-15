#include <states/SandBoxState.hpp>
#include <map>
#include <string>
#include <queue>
#include <list>
#include <iostream>

class Window;

class SandBoxStateManager
{
    public:
        SandBoxStateManager() = default;
        ~SandBoxStateManager() = default;

        void Run();
        void ChangeState(ISandBoxState* state);
        void PushState(ISandBoxState* state);
        void PopState();
        void PerformStateChange();
        ISandBoxState* GetCurrentState();
        ISandBoxState* GetNextState();
        bool NeedToChangeState() const;
        bool HasStates() const;
        int GetSize() const;

    private:
        std::list<ISandBoxState*> m_statesStack; 
        ISandBoxState* m_currentState;
        ISandBoxState* m_nextState;
        ISandBoxState* m_stateToMove;
};