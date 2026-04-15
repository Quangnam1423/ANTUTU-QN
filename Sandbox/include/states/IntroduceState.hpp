#ifndef INTRODUCE_STATE_HPP
#define INTRODUCE_STATE_HPP

#include <states/ISandBoxState.hpp>

#include <iostream>
#include <string>
#include <list>

class IntroduceState : public ISandBoxState
{
    public:
        IntroduceState() = default;
        ~IntroduceState() override = default;
        void Init() override;
        void Cleanup() override;
        void Update(float deltaTime) override;
        void Render() override;
        void Pause() override;
        void Resume() override;
        void Exit() override;
        bool IsFinished() const override;
    private:
        bool m_isInitialized;
        bool m_isFinished;
        SandBoxState m_currentState;
};

#endif // INTRODUCE_STATE_HPP
