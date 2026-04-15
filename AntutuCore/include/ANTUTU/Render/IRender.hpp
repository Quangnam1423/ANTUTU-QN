#ifndef ANTUTU_RENDER_IRENDER_HPP
#define ANTUTU_RENDER_IRENDER_HPP

#include <ANTUTU/VulkanCommon.hpp>

namespace att::Render
{
    class ANTUTU_API IRenderable 
    {
    public:
        virtual ~IRenderable() = default;
        virtual bool Initialize() = 0;
        virtual void Render() = 0;
        virtual void OnResize(uint32_t width, uint32_t height) = 0;
        virtual void OnScale(float scaleX, float scaleY) = 0;
        virtual void Destroy() = 0;
    };
}

#endif // ANTUTU_RENDER_IRENDER_HPP