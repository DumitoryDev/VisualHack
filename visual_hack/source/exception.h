#pragma once
#include <utility>
#include "../pch.h"
namespace  error
{
	class c_exception
	{

	public:

		c_exception(const c_exception&) = default;
		c_exception(c_exception&&) = default;
		c_exception& operator = (const c_exception&) = default;
		c_exception& operator = (c_exception&&) = default;

	protected:

		std::wstring m_wsMessage{};
		using ULONG = unsigned long;
		ULONG m_ulCode{};

	public:

		explicit c_exception(const std::wstring& wsMessage) : c_exception(wsMessage, {}) { }

		explicit c_exception(ULONG ulCode) : c_exception({}, ulCode) { }

		explicit c_exception(std::wstring wsMessage,
			ULONG ulCode) : m_wsMessage(std::move(wsMessage)), m_ulCode(ulCode) { }

		virtual ~c_exception(void) = default;

		virtual std::wstring GetMessage(void) const
		{

			return this->m_wsMessage;

		}

		auto get_code(void) const noexcept
		{

			return this->m_ulCode;

		}

	};
	

	class c_win_api_exception : public c_exception
	{

	public:

		using c_exception::c_exception;

		std::wstring GetMessage(void) const override
		{

			if (!c_exception::m_ulCode)
				return c_exception::m_wsMessage;

			LPVOID lpMsgBuf{};

			if (!FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
				{},
				c_exception::m_ulCode,
				MAKELANGID(LANG_ENGLISH, SUBLANG_DEFAULT),
				reinterpret_cast<LPWSTR>(&lpMsgBuf),
				{},
				{}))
				return c_exception::m_wsMessage;

			std::wostringstream wos{};
			wos << c_exception::m_wsMessage << std::endl;
			wos << L"Error code " << c_exception::m_ulCode << std::endl;
			wos << reinterpret_cast<LPCWSTR>(lpMsgBuf);

			::LocalFree(lpMsgBuf);

			return wos.str();

		}

	};




}
