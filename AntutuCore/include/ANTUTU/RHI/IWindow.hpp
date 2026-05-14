#ifndef I_WINDOW_CORE_HPP
#define I_WINDOW_CORE_HPP

#include <ANTUTU/RHI/ISurfaceProvider.hpp>

namespace att::RHI
{
	class ANTUTU_API IWindow : public ISurfaceProvider
	{
	public:
		virtual ~IWindow() = default;

        virtual void Update() = 0;

        virtual bool ShouldClose() const = 0;

        virtual uint32_t GetWidth() const = 0;

        virtual uint32_t GetHeight() const = 0;

        virtual void* GetNativeWindow() const = 0;
	};
}

#endif // I_WINDOW_CORE_HPP