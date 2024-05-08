#pragma once


namespace ngl
{
	enum ELOG
	{
		ELOG_DEBUG,   // ������Ϣ
		ELOG_INFO,    // ��ӡ
		ELOG_WARN,    // ����
		ELOG_ERROR,   // ����
		ELOG_NONE,    // ��
	};

	struct sysconfig
	{
	private:
		//##### ��־���
		static ELOG		m_loglevel;			// ��־�ȼ�
		static int32_t	m_logline;			// ������־�ļ�������
		static int32_t	m_logflushtime;		// ��־flushʱ��
		static bool		m_logiswrite;		// ��־�Ƿ�д���ļ�
		static bool		m_logconsole;		// �Ƿ��ӡ������̨

		static int32_t	m_consumings;		// ���actor��Ϣ��ʱ

		// ���ü򵥼���
		static std::string	m_xorkey;
		static int32_t		m_xorkeynum;	//2^n-1 nΪxorkey���ַ���
		static bool			m_isxor;
		
		static bool			m_varint;		// �Ƿ���varint

		static bool			m_robot_test;	// �Ƿ�����˲���
	public:
		static void init();

		static ELOG loglevel()
		{ 
			return m_loglevel;
		}
	
		static int32_t logline()
		{
			return m_logline;
		}

		static int32_t logflushtime()
		{
			return m_logflushtime;
		}

		static bool logiswrite()
		{
			return m_logiswrite;
		}

		static bool logconsole()
		{
			return m_logconsole;
		}

		static int32_t consumings()
		{
			return m_consumings;
		}

		static std::string& xorkey()
		{
			return m_xorkey;
		}

		static int32_t xorkeynum()
		{
			return m_xorkeynum;
		}

		static bool isxor()
		{
			return m_isxor;
		}

		static bool varint()
		{
			return m_varint;
		}

		static bool robot_test()
		{
			return m_robot_test;
		}
	};
}//namespace ngl