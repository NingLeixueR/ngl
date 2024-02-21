namespace ngl
{
	enum ENET_CONFIG
	{
		net_config_send_buff_maxbyte = 8129,	
		net_config_recv_buff_maxbyte = 8129,	
		net_config_logic_pthread_max_size = 8,	
		net_config_socket_pthread_max_size = 8,	
	}
	partial class rcsv
	{
		public static bool readcsv(csvpair apair, List<ENET_CONFIG> avec)
		{
			string ltempstr = read(apair);
			csvpair lpair = new csvpair();
			lpair.m_data = ltempstr;
			lpair.m_fg = '*';
			for (; !isok(lpair);)
			{
				Int32 ltemp = 0;
				if (readcsv(lpair, ref ltemp))
					avec.Add((ENET_CONFIG)ltemp);
			}
			return true;
		}
	}
	enum EUDP_OPERATOR
	{
		EUDP_OPERATOR_ACK,	// ȷ�ϰ�
		EUDP_OPERATOR_DATA,	// ���������ݰ�
		EUDP_OPERATOR_HEARTBEAT,	// ������Ҫ����ȷ�϶Զ��Ƿ�����
	}
	partial class rcsv
	{
		public static bool readcsv(csvpair apair, List<EUDP_OPERATOR> avec)
		{
			string ltempstr = read(apair);
			csvpair lpair = new csvpair();
			lpair.m_data = ltempstr;
			lpair.m_fg = '*';
			for (; !isok(lpair);)
			{
				Int32 ltemp = 0;
				if (readcsv(lpair, ref ltemp))
					avec.Add((EUDP_OPERATOR)ltemp);
			}
			return true;
		}
	}
	enum EPH_HEAD_VAL
	{
		EPH_HEAD_VERSION_SUCCESS = 1,	// �汾һ��
		EPH_HEAD_VERSION_FAIL = 2,	// �汾��һ��
		EPH_HEAD_VERSION_FOLLOW = 3,	// �޷��ԱȰ汾,����û�н������
		EPH_HEAD_FOLLOW = 4,	// ��ͷ����û�н������
		EPH_HEAD_SUCCESS = 5,	// ��ͷ�����ѽ������
	}
	partial class rcsv
	{
		public static bool readcsv(csvpair apair, List<EPH_HEAD_VAL> avec)
		{
			string ltempstr = read(apair);
			csvpair lpair = new csvpair();
			lpair.m_data = ltempstr;
			lpair.m_fg = '*';
			for (; !isok(lpair);)
			{
				Int32 ltemp = 0;
				if (readcsv(lpair, ref ltemp))
					avec.Add((EPH_HEAD_VAL)ltemp);
			}
			return true;
		}
	}
	enum EPH
	{
		EPH_VERSION = 0,	// Э��汾��
		EPH_BYTES,	// Э���ֽ���
		EPH_TIME,	// ���Ͷ˵�ʱ���
		EPH_PROTOCOLNUM,	// Э���
		EPH_PROTOCOLTYPE,	// Э������ EPROTOCOL_TYPE
		EPH_ACTOR_TYPEAREA,	// ACTOR_TYPE_AREA
		EPH_ACTOR_ID,	// ACTOR_ID
		EPH_REQUEST_ACTOR_TYPEAREA,	// Request REQUEST_ACTOR_TYPE_AREA
		EPH_REQUEST_ACTOR_ID,	// Request ACTOR_ID
		EPH_SUM,	
	}
	partial class rcsv
	{
		public static bool readcsv(csvpair apair, List<EPH> avec)
		{
			string ltempstr = read(apair);
			csvpair lpair = new csvpair();
			lpair.m_data = ltempstr;
			lpair.m_fg = '*';
			for (; !isok(lpair);)
			{
				Int32 ltemp = 0;
				if (readcsv(lpair, ref ltemp))
					avec.Add((EPH)ltemp);
			}
			return true;
		}
	}
	enum NODE_TYPE
	{
		DB = 1,	// ���ݿ������
		ACTORSERVER = 2,	// actor ������
		GAME = 3,	// �߼�������
		GATEWAY = 4,	// ���ط�����
		LOGIN = 5,	// ��¼������
		ROBOT = 6,	// ���Ի����˷�����
		WORLD = 7,	// ���������
		LOG = 8,	// ��־������
		RELOADCSV = 9,	// ���طַ�csv������
		CROSS = 10,	// ���������
		CROSSDB = 11,	// ������ݿ������
		PUSHSERVERCONFIG = 12,	// �������������ϴ�lbgmsys
		FAIL = -1,	// ���������ʹ���
	}
	partial class rcsv
	{
		public static bool readcsv(csvpair apair, List<NODE_TYPE> avec)
		{
			string ltempstr = read(apair);
			csvpair lpair = new csvpair();
			lpair.m_data = ltempstr;
			lpair.m_fg = '*';
			for (; !isok(lpair);)
			{
				Int32 ltemp = 0;
				if (readcsv(lpair, ref ltemp))
					avec.Add((NODE_TYPE)ltemp);
			}
			return true;
		}
	}
	enum ENET_PROTOCOL
	{
		ENET_TCP = 1,	
		ENET_UDP = 2,	
		ENET_WS = 3,	
		ENET_KCP = 4,	
	}
	partial class rcsv
	{
		public static bool readcsv(csvpair apair, List<ENET_PROTOCOL> avec)
		{
			string ltempstr = read(apair);
			csvpair lpair = new csvpair();
			lpair.m_data = ltempstr;
			lpair.m_fg = '*';
			for (; !isok(lpair);)
			{
				Int32 ltemp = 0;
				if (readcsv(lpair, ref ltemp))
					avec.Add((ENET_PROTOCOL)ltemp);
			}
			return true;
		}
	}
	enum EnumModule
	{
		E_ModuleNull = 0,	// ��	
		E_ModuleRoot = 1,	// ����(��β)
		E_ModuleBuff = 2,	// ���buff
		E_ModuleEquip = 3,	// װ��
		E_ModuleEquipWeapon = 4,	// װ������
		E_ModuleEquipHelmet = 5,	// װ��ͷ��
		E_ModuleEquipCloth = 6,	// װ���·�
		E_ModuleEquipPants = 7,	// װ������
		E_ModuleCount = 8,	// ���� 	
	}
	partial class rcsv
	{
		public static bool readcsv(csvpair apair, List<EnumModule> avec)
		{
			string ltempstr = read(apair);
			csvpair lpair = new csvpair();
			lpair.m_data = ltempstr;
			lpair.m_fg = '*';
			for (; !isok(lpair);)
			{
				Int32 ltemp = 0;
				if (readcsv(lpair, ref ltemp))
					avec.Add((EnumModule)ltemp);
			}
			return true;
		}
	}
	enum EnumAttribute
	{
		E_Null = 0,	
		E_Attack = 1,	// [����]
		E_Defense = 2,	// [����]
		E_Hp = 3,	// [Ѫ��]
		E_Anger = 4,	// [ŭ��]
		E_Speed = 5,	// [�ٶ�]
		E_Count = 6,	
	}
	partial class rcsv
	{
		public static bool readcsv(csvpair apair, List<EnumAttribute> avec)
		{
			string ltempstr = read(apair);
			csvpair lpair = new csvpair();
			lpair.m_data = ltempstr;
			lpair.m_fg = '*';
			for (; !isok(lpair);)
			{
				Int32 ltemp = 0;
				if (readcsv(lpair, ref ltemp))
					avec.Add((EnumAttribute)ltemp);
			}
			return true;
		}
	}
	enum EItemSrc
	{
		EItemSrcNoraml = 0,	
		EItemSrcGM = 1,	
	}
	partial class rcsv
	{
		public static bool readcsv(csvpair apair, List<EItemSrc> avec)
		{
			string ltempstr = read(apair);
			csvpair lpair = new csvpair();
			lpair.m_data = ltempstr;
			lpair.m_fg = '*';
			for (; !isok(lpair);)
			{
				Int32 ltemp = 0;
				if (readcsv(lpair, ref ltemp))
					avec.Add((EItemSrc)ltemp);
			}
			return true;
		}
	}
	enum EItemConsume
	{
		EItemConsumeNoraml = 0,	
		EItemConsumeGM = 1,	
	}
	partial class rcsv
	{
		public static bool readcsv(csvpair apair, List<EItemConsume> avec)
		{
			string ltempstr = read(apair);
			csvpair lpair = new csvpair();
			lpair.m_data = ltempstr;
			lpair.m_fg = '*';
			for (; !isok(lpair);)
			{
				Int32 ltemp = 0;
				if (readcsv(lpair, ref ltemp))
					avec.Add((EItemConsume)ltemp);
			}
			return true;
		}
	}
	enum EItemType
	{
		EEquipment = 1,	// װ��
		EMaterial = 2,	// ����
		EMoneyGold = 3,	// ���
		EMoneySilver = 4,	// ����
		ECard = 5,	// ����
	}
	partial class rcsv
	{
		public static bool readcsv(csvpair apair, List<EItemType> avec)
		{
			string ltempstr = read(apair);
			csvpair lpair = new csvpair();
			lpair.m_data = ltempstr;
			lpair.m_fg = '*';
			for (; !isok(lpair);)
			{
				Int32 ltemp = 0;
				if (readcsv(lpair, ref ltemp))
					avec.Add((EItemType)ltemp);
			}
			return true;
		}
	}
	enum EQuality
	{
		EQualityGrey = 0,	//��ɫ
		EQualityGreen = 1,	//��ɫ
		EQualityYellow = 2,	//��ɫ
		EQualityOrange = 3,	//��ɫ
		EQualityRed = 4,	//��ɫ
	}
	partial class rcsv
	{
		public static bool readcsv(csvpair apair, List<EQuality> avec)
		{
			string ltempstr = read(apair);
			csvpair lpair = new csvpair();
			lpair.m_data = ltempstr;
			lpair.m_fg = '*';
			for (; !isok(lpair);)
			{
				Int32 ltemp = 0;
				if (readcsv(lpair, ref ltemp))
					avec.Add((EQuality)ltemp);
			}
			return true;
		}
	}
	enum EEquip
	{
		EEquipWeapon = 1,	// ����
		EEquipHelmet = 2,	// ͷ��
		EEquipCloth = 3,	// �·�
		EEquipPants = 4,	// ����
	}
	partial class rcsv
	{
		public static bool readcsv(csvpair apair, List<EEquip> avec)
		{
			string ltempstr = read(apair);
			csvpair lpair = new csvpair();
			lpair.m_data = ltempstr;
			lpair.m_fg = '*';
			for (; !isok(lpair);)
			{
				Int32 ltemp = 0;
				if (readcsv(lpair, ref ltemp))
					avec.Add((EEquip)ltemp);
			}
			return true;
		}
	}
	enum ECalendar
	{
		Week = 0,	// �ܼ�
		ServerOpen = 1,	// �Կ���ʱ������������
		RegularSlot = 2,	// �̶�ʱ���
	}
	partial class rcsv
	{
		public static bool readcsv(csvpair apair, List<ECalendar> avec)
		{
			string ltempstr = read(apair);
			csvpair lpair = new csvpair();
			lpair.m_data = ltempstr;
			lpair.m_fg = '*';
			for (; !isok(lpair);)
			{
				Int32 ltemp = 0;
				if (readcsv(lpair, ref ltemp))
					avec.Add((ECalendar)ltemp);
			}
			return true;
		}
	}
	enum EActivity
	{
		EActivityDrawCompliance = 1,	// ��������֮����<<��ļ���>>
	}
	partial class rcsv
	{
		public static bool readcsv(csvpair apair, List<EActivity> avec)
		{
			string ltempstr = read(apair);
			csvpair lpair = new csvpair();
			lpair.m_data = ltempstr;
			lpair.m_fg = '*';
			for (; !isok(lpair);)
			{
				Int32 ltemp = 0;
				if (readcsv(lpair, ref ltemp))
					avec.Add((EActivity)ltemp);
			}
			return true;
		}
	}
	enum ETask
	{
		ETaskRoleLv = 1,	// ��ҵȼ�
		ETaskRoleVip = 2,	// ���vip�ȼ�
		ETaskTaskId = 3,	// ���ĳID����
	}
	partial class rcsv
	{
		public static bool readcsv(csvpair apair, List<ETask> avec)
		{
			string ltempstr = read(apair);
			csvpair lpair = new csvpair();
			lpair.m_data = ltempstr;
			lpair.m_fg = '*';
			for (; !isok(lpair);)
			{
				Int32 ltemp = 0;
				if (readcsv(lpair, ref ltemp))
					avec.Add((ETask)ltemp);
			}
			return true;
		}
	}
	enum ETaskType
	{
		ETaskTypePrincipalLine,	// ��������
		ETaskTypeBranchLine,	// ֧������
		ETaskTypeDaily,	// ÿ������
	}
	partial class rcsv
	{
		public static bool readcsv(csvpair apair, List<ETaskType> avec)
		{
			string ltempstr = read(apair);
			csvpair lpair = new csvpair();
			lpair.m_data = ltempstr;
			lpair.m_fg = '*';
			for (; !isok(lpair);)
			{
				Int32 ltemp = 0;
				if (readcsv(lpair, ref ltemp))
					avec.Add((ETaskType)ltemp);
			}
			return true;
		}
	}
	enum eobstacles
	{
		eobstacles_pass = 0,	// ����ͨ��
		eobstacles_nopass = 1,	// �޷�ͨ��
	}
	partial class rcsv
	{
		public static bool readcsv(csvpair apair, List<eobstacles> avec)
		{
			string ltempstr = read(apair);
			csvpair lpair = new csvpair();
			lpair.m_data = ltempstr;
			lpair.m_fg = '*';
			for (; !isok(lpair);)
			{
				Int32 ltemp = 0;
				if (readcsv(lpair, ref ltemp))
					avec.Add((eobstacles)ltemp);
			}
			return true;
		}
	}
	class tab_servers : ICsvRead, ICsv
	{
		/*********************************/
		public Int32		m_id;		
		public string		m_name;		
		public string		m_remarks;		
		public Int16		m_area;		// ����
		public NODE_TYPE		m_type;		// ����������(1db2actorserver3game4gateway5login6robot7world8log9reloadcsv10reloadcsv_tools)
		public Int32		m_tcount;		// ͬ���ͷ����������
		public ENET_PROTOCOL		m_net;		// ������Э��(1tcp2udp3ws)
		public string		m_ip;		// ip
		public string		m_nip;		// ����ip
		public Int16		m_port;		// �˿�
		public Int32		m_threadnum;		// socket�߳���
		public Int32		m_actorthreadnum;		// actor�̳߳��߳���
		public bool		m_outernet;		// �Ƿ�������������
		public Int32		m_db;		// ���ӵ�db����id
		public Int32		m_reloadcsv;		// ���ӵ�reloadcsv����id
		public Int32		m_login;		// ���ӵ�login����id
		public Int16		m_crossarea;		// �������
		public bool		m_isopenkcp;		// �Ƿ���kcp(m_port+10000)
		public List<Int32>		m_actorserver = new List<Int32>();		// ���ӵ�actorserver����id(�����Ҫ��д���actorserver)
		/*********************************/
		public Int32 Id(){return m_id;}
		public bool Read(csvpair apair)
		{
			if(rcsv.readcsv(apair, ref m_id) == false)
				return false;
			if(rcsv.readcsv(apair, ref m_name) == false)
				return false;
			if(rcsv.readcsv(apair, ref m_remarks) == false)
				return false;
			if(rcsv.readcsv(apair, ref m_area) == false)
				return false;
			Int32 lm_type = 0;
			if(rcsv.readcsv(apair, ref lm_type) == false)
				return false;
			m_type = (NODE_TYPE)lm_type;
			if(rcsv.readcsv(apair, ref m_tcount) == false)
				return false;
			Int32 lm_net = 0;
			if(rcsv.readcsv(apair, ref lm_net) == false)
				return false;
			m_net = (ENET_PROTOCOL)lm_net;
			if(rcsv.readcsv(apair, ref m_ip) == false)
				return false;
			if(rcsv.readcsv(apair, ref m_nip) == false)
				return false;
			if(rcsv.readcsv(apair, ref m_port) == false)
				return false;
			if(rcsv.readcsv(apair, ref m_threadnum) == false)
				return false;
			if(rcsv.readcsv(apair, ref m_actorthreadnum) == false)
				return false;
			if(rcsv.readcsv(apair, ref m_outernet) == false)
				return false;
			if(rcsv.readcsv(apair, ref m_db) == false)
				return false;
			if(rcsv.readcsv(apair, ref m_reloadcsv) == false)
				return false;
			if(rcsv.readcsv(apair, ref m_login) == false)
				return false;
			if(rcsv.readcsv(apair, ref m_crossarea) == false)
				return false;
			if(rcsv.readcsv(apair, ref m_isopenkcp) == false)
				return false;
			if(rcsv.readcsv(apair, m_actorserver) == false)
				return false;
			return true;
		}
	}
	class tab_dbload : ICsvRead, ICsv
	{
		/*********************************/
		public Int32		m_id;		
		public string		m_name;		
		public string		m_remarks;		
		public bool		m_isloadall;		// �Ƿ���Ҫ��������ȫ������
		public bool		m_network;		// �Ƿ�����ͨ������ַ�
		public Int32		m_sendmaxcount;		// ������෢������
		/*********************************/
		public Int32 Id(){return m_id;}
		public bool Read(csvpair apair)
		{
			if(rcsv.readcsv(apair, ref m_id) == false)
				return false;
			if(rcsv.readcsv(apair, ref m_name) == false)
				return false;
			if(rcsv.readcsv(apair, ref m_remarks) == false)
				return false;
			if(rcsv.readcsv(apair, ref m_isloadall) == false)
				return false;
			if(rcsv.readcsv(apair, ref m_network) == false)
				return false;
			if(rcsv.readcsv(apair, ref m_sendmaxcount) == false)
				return false;
			return true;
		}
	}
	class tab_errormessage : ICsvRead, ICsv
	{
		/*********************************/
		public Int32		m_id;		
		public string		m_name;		
		public string		m_remarks;		
		public string		m_message;		// ��������
		/*********************************/
		public Int32 Id(){return m_id;}
		public bool Read(csvpair apair)
		{
			if(rcsv.readcsv(apair, ref m_id) == false)
				return false;
			if(rcsv.readcsv(apair, ref m_name) == false)
				return false;
			if(rcsv.readcsv(apair, ref m_remarks) == false)
				return false;
			if(rcsv.readcsv(apair, ref m_message) == false)
				return false;
			return true;
		}
	}
	class tab_specialid : ICsvRead, ICsv
	{
		/*********************************/
		public Int32		m_id;		
		public string		m_name;		
		public string		m_remarks;		
		public string		m_value;		
		/*********************************/
		public Int32 Id(){return m_id;}
		public bool Read(csvpair apair)
		{
			if(rcsv.readcsv(apair, ref m_id) == false)
				return false;
			if(rcsv.readcsv(apair, ref m_name) == false)
				return false;
			if(rcsv.readcsv(apair, ref m_remarks) == false)
				return false;
			if(rcsv.readcsv(apair, ref m_value) == false)
				return false;
			return true;
		}
	}
	class tab_attribute : ICsvRead, ICsv
	{
		/*********************************/
		public Int32		m_id;		
		public string		m_name;		
		public string		m_remarks;		
		public float		m_fightcoefficient;		// �����ṩ��ս��ϵ��
		public Int32		m_initvalue;		// ���Գ�ʼֵ
		public Int32		m_uplimit;		// ����
		public Int32		m_lowlimit;		// ����
		/*********************************/
		public Int32 Id(){return m_id;}
		public bool Read(csvpair apair)
		{
			if(rcsv.readcsv(apair, ref m_id) == false)
				return false;
			if(rcsv.readcsv(apair, ref m_name) == false)
				return false;
			if(rcsv.readcsv(apair, ref m_remarks) == false)
				return false;
			if(rcsv.readcsv(apair, ref m_fightcoefficient) == false)
				return false;
			if(rcsv.readcsv(apair, ref m_initvalue) == false)
				return false;
			if(rcsv.readcsv(apair, ref m_uplimit) == false)
				return false;
			if(rcsv.readcsv(apair, ref m_lowlimit) == false)
				return false;
			return true;
		}
	}
	class tab_item : ICsvRead, ICsv
	{
		/*********************************/
		public Int32		m_id;		
		public string		m_name;		
		public string		m_remarks;		
		public Int32		m_ranks;		// ����ֵ
		public EItemType		m_type;		// ��Ʒ����EItemType(1װ��,2����,3���,4����)
		public Int32		m_quality;		// ��ƷƷ��(EQuality)
		public bool		m_isstack;		// �Ƿ�ɶѵ�
		/*********************************/
		public Int32 Id(){return m_id;}
		public bool Read(csvpair apair)
		{
			if(rcsv.readcsv(apair, ref m_id) == false)
				return false;
			if(rcsv.readcsv(apair, ref m_name) == false)
				return false;
			if(rcsv.readcsv(apair, ref m_remarks) == false)
				return false;
			if(rcsv.readcsv(apair, ref m_ranks) == false)
				return false;
			Int32 lm_type = 0;
			if(rcsv.readcsv(apair, ref lm_type) == false)
				return false;
			m_type = (EItemType)lm_type;
			if(rcsv.readcsv(apair, ref m_quality) == false)
				return false;
			if(rcsv.readcsv(apair, ref m_isstack) == false)
				return false;
			return true;
		}
	}
	class attributevalue : ICsvRead
	{
		/*********************************/
		public Int32		m_id;		// ����id(EnumAttribute)
		public bool		m_isratio;		// �Ƿ���ֱ�����
		public Int32		m_value;		// ����ֵ
		/*********************************/
		public bool Read(csvpair apair)
		{
			if(rcsv.readcsv(apair, ref m_id) == false)
				return false;
			if(rcsv.readcsv(apair, ref m_isratio) == false)
				return false;
			if(rcsv.readcsv(apair, ref m_value) == false)
				return false;
			return true;
		}
	}
	class tab_equip : ICsvRead, ICsv
	{
		/*********************************/
		public Int32		m_id;		
		public string		m_name;		
		public string		m_remarks;		
		public EEquip		m_position;		// ��λEEquip(1����2ͷ��3�·�4����)
		public List<attributevalue>		m_attributevalues = new List<attributevalue>();		// װ������
		/*********************************/
		public Int32 Id(){return m_id;}
		public bool Read(csvpair apair)
		{
			if(rcsv.readcsv(apair, ref m_id) == false)
				return false;
			if(rcsv.readcsv(apair, ref m_name) == false)
				return false;
			if(rcsv.readcsv(apair, ref m_remarks) == false)
				return false;
			Int32 lm_position = 0;
			if(rcsv.readcsv(apair, ref lm_position) == false)
				return false;
			m_position = (EEquip)lm_position;
			if(rcsv.readcsv(apair, m_attributevalues) == false)
				return false;
			return true;
		}
	}
	class tab_equiplv : ICsvRead, ICsv
	{
		/*********************************/
		public Int32		m_id;		
		public string		m_name;		
		public string		m_remarks;		
		public Int32		m_consume;		// ��������id
		public List<attributevalue>		m_attributevalues = new List<attributevalue>();		// װ������
		/*********************************/
		public Int32 Id(){return m_id;}
		public bool Read(csvpair apair)
		{
			if(rcsv.readcsv(apair, ref m_id) == false)
				return false;
			if(rcsv.readcsv(apair, ref m_name) == false)
				return false;
			if(rcsv.readcsv(apair, ref m_remarks) == false)
				return false;
			if(rcsv.readcsv(apair, ref m_consume) == false)
				return false;
			if(rcsv.readcsv(apair, m_attributevalues) == false)
				return false;
			return true;
		}
	}
	class tab_card : ICsvRead, ICsv
	{
		/*********************************/
		public Int32		m_id;		
		public string		m_name;		
		public string		m_remarks;		
		public EQuality		m_quality;		// Ʒ��EQuality(0��ɫ1��ɫ2��ɫ3��ɫ4��ɫ)
		public List<attributevalue>		m_attributevalues = new List<attributevalue>();		// ����
		/*********************************/
		public Int32 Id(){return m_id;}
		public bool Read(csvpair apair)
		{
			if(rcsv.readcsv(apair, ref m_id) == false)
				return false;
			if(rcsv.readcsv(apair, ref m_name) == false)
				return false;
			if(rcsv.readcsv(apair, ref m_remarks) == false)
				return false;
			Int32 lm_quality = 0;
			if(rcsv.readcsv(apair, ref lm_quality) == false)
				return false;
			m_quality = (EQuality)lm_quality;
			if(rcsv.readcsv(apair, m_attributevalues) == false)
				return false;
			return true;
		}
	}
	class trandom : ICsvRead
	{
		/*********************************/
		public Int32		m_id;		
		public Int32		m_min;		
		public Int32		m_max;		
		public Int32		m_weight;		
		/*********************************/
		public bool Read(csvpair apair)
		{
			if(rcsv.readcsv(apair, ref m_id) == false)
				return false;
			if(rcsv.readcsv(apair, ref m_min) == false)
				return false;
			if(rcsv.readcsv(apair, ref m_max) == false)
				return false;
			if(rcsv.readcsv(apair, ref m_weight) == false)
				return false;
			return true;
		}
	}
	class tab_random : ICsvRead, ICsv
	{
		/*********************************/
		public Int32		m_id;		
		public string		m_name;		
		public string		m_remarks;		
		public bool		m_exclusive;		// �����Զ�ε���ʱʹ�ã�true���������ѵ�����Ʒ false�������ѵ�����Ʒ��
		public Int32		m_count;		// �������
		public Int32		m_calendarids;		// �Ƿ����������,ֻ�����������Ż�ִ�д˵���
		public List<trandom>		m_randomdatas = new List<trandom>();		// trandom(id*min*max*weight)
		public List<Int32>		m_childrandomids = new List<Int32>();		// �����
		/*********************************/
		public Int32 Id(){return m_id;}
		public bool Read(csvpair apair)
		{
			if(rcsv.readcsv(apair, ref m_id) == false)
				return false;
			if(rcsv.readcsv(apair, ref m_name) == false)
				return false;
			if(rcsv.readcsv(apair, ref m_remarks) == false)
				return false;
			if(rcsv.readcsv(apair, ref m_exclusive) == false)
				return false;
			if(rcsv.readcsv(apair, ref m_count) == false)
				return false;
			if(rcsv.readcsv(apair, ref m_calendarids) == false)
				return false;
			if(rcsv.readcsv(apair, m_randomdatas) == false)
				return false;
			if(rcsv.readcsv(apair, m_childrandomids) == false)
				return false;
			return true;
		}
	}
	class tconsume : ICsvRead
	{
		/*********************************/
		public Int32		m_tid;		
		public Int32		m_count;		
		/*********************************/
		public bool Read(csvpair apair)
		{
			if(rcsv.readcsv(apair, ref m_tid) == false)
				return false;
			if(rcsv.readcsv(apair, ref m_count) == false)
				return false;
			return true;
		}
	}
	class tab_consume : ICsvRead, ICsv
	{
		/*********************************/
		public Int32		m_id;		
		public string		m_name;		
		public string		m_remarks;		
		public List<tconsume>		m_consumeitems = new List<tconsume>();		// tid*count
		/*********************************/
		public Int32 Id(){return m_id;}
		public bool Read(csvpair apair)
		{
			if(rcsv.readcsv(apair, ref m_id) == false)
				return false;
			if(rcsv.readcsv(apair, ref m_name) == false)
				return false;
			if(rcsv.readcsv(apair, ref m_remarks) == false)
				return false;
			if(rcsv.readcsv(apair, m_consumeitems) == false)
				return false;
			return true;
		}
	}
	class tab_synthesis : ICsvRead, ICsv
	{
		/*********************************/
		public Int32		m_id;		
		public string		m_name;		
		public string		m_remarks;		
		public Int32		m_consume;		// �����б�
		public Int32		m_generate;		// �����(tab_rando)id ����ɹ���Ʒ�б�
		/*********************************/
		public Int32 Id(){return m_id;}
		public bool Read(csvpair apair)
		{
			if(rcsv.readcsv(apair, ref m_id) == false)
				return false;
			if(rcsv.readcsv(apair, ref m_name) == false)
				return false;
			if(rcsv.readcsv(apair, ref m_remarks) == false)
				return false;
			if(rcsv.readcsv(apair, ref m_consume) == false)
				return false;
			if(rcsv.readcsv(apair, ref m_generate) == false)
				return false;
			return true;
		}
	}
	class tweek : ICsvRead
	{
		/*********************************/
		public Int32		m_week;		// �ܼ�
		public string		m_opentime;		//  ����ʱ�� HH:mm:ss
		public string		m_closetime;		//  ����ʱ�� HH:mm:ss
		/*********************************/
		public bool Read(csvpair apair)
		{
			if(rcsv.readcsv(apair, ref m_week) == false)
				return false;
			if(rcsv.readcsv(apair, ref m_opentime) == false)
				return false;
			if(rcsv.readcsv(apair, ref m_closetime) == false)
				return false;
			return true;
		}
	}
	class tserveropen : ICsvRead
	{
		/*********************************/
		public Int32		m_beg;		// ����������쿪��
		public string		m_opentime;		// ����ʱ�� HH:mm:ss
		public Int32		m_end;		// ��������������
		public string		m_closetime;		// ����ʱ�� HH:mm:ss
		/*********************************/
		public bool Read(csvpair apair)
		{
			if(rcsv.readcsv(apair, ref m_beg) == false)
				return false;
			if(rcsv.readcsv(apair, ref m_opentime) == false)
				return false;
			if(rcsv.readcsv(apair, ref m_end) == false)
				return false;
			if(rcsv.readcsv(apair, ref m_closetime) == false)
				return false;
			return true;
		}
	}
	class tregularslot : ICsvRead
	{
		/*********************************/
		public string		m_opentime;		// ����ʱ�� YYYY-MM-DD HH:mm:ss
		public string		m_closetime;		// ����ʱ�� YYYY-MM-DD HH:mm:ss
		/*********************************/
		public bool Read(csvpair apair)
		{
			if(rcsv.readcsv(apair, ref m_opentime) == false)
				return false;
			if(rcsv.readcsv(apair, ref m_closetime) == false)
				return false;
			return true;
		}
	}
	class tab_calendar : ICsvRead, ICsv
	{
		/*********************************/
		public Int32		m_id;		
		public string		m_name;		
		public string		m_remarks;		
		public ECalendar		m_type;		//ECalendar(0:�ܼ�,1:�Կ���ʱ������������,2:�̶�ʱ���)
		public List<tweek>		m_week = new List<tweek>();		//m_type=0,tweek(�ܼ�(1-7)*����ʱ��HH:mm:ss*����ʱ��HH:mm:ss)
		public List<tserveropen>		m_serveropen = new List<tserveropen>();		//m_type=1,tserveropen(����������쿪��*����ʱ��HH:mm:ss*��������������*����ʱ��HH:mm:ss)
		public List<tregularslot>		m_tregularslot = new List<tregularslot>();		//m_type=2,tregularslot(����ʱ��YYYY/MM/DD HH:mm:ss*����ʱ��YYYY/MM/DD HH:mm:ss)
		/*********************************/
		public Int32 Id(){return m_id;}
		public bool Read(csvpair apair)
		{
			if(rcsv.readcsv(apair, ref m_id) == false)
				return false;
			if(rcsv.readcsv(apair, ref m_name) == false)
				return false;
			if(rcsv.readcsv(apair, ref m_remarks) == false)
				return false;
			Int32 lm_type = 0;
			if(rcsv.readcsv(apair, ref lm_type) == false)
				return false;
			m_type = (ECalendar)lm_type;
			if(rcsv.readcsv(apair, m_week) == false)
				return false;
			if(rcsv.readcsv(apair, m_serveropen) == false)
				return false;
			if(rcsv.readcsv(apair, m_tregularslot) == false)
				return false;
			return true;
		}
	}
	class tab_mail : ICsvRead, ICsv
	{
		/*********************************/
		public Int32		m_id;		
		public string		m_name;		
		public string		m_remarks;		
		public string		m_title;		// �ʼ�����
		public string		m_author;		// �ʼ�����
		public string		m_content;		// �ʼ�����
		/*********************************/
		public Int32 Id(){return m_id;}
		public bool Read(csvpair apair)
		{
			if(rcsv.readcsv(apair, ref m_id) == false)
				return false;
			if(rcsv.readcsv(apair, ref m_name) == false)
				return false;
			if(rcsv.readcsv(apair, ref m_remarks) == false)
				return false;
			if(rcsv.readcsv(apair, ref m_title) == false)
				return false;
			if(rcsv.readcsv(apair, ref m_author) == false)
				return false;
			if(rcsv.readcsv(apair, ref m_content) == false)
				return false;
			return true;
		}
	}
	class tab_chat : ICsvRead, ICsv
	{
		/*********************************/
		public Int32		m_id;		
		public string		m_name;		
		public string		m_remarks;		
		public Int32		m_time;		// ���췢�Լ��
		public Int32		m_count;		// ���췢���������
		/*********************************/
		public Int32 Id(){return m_id;}
		public bool Read(csvpair apair)
		{
			if(rcsv.readcsv(apair, ref m_id) == false)
				return false;
			if(rcsv.readcsv(apair, ref m_name) == false)
				return false;
			if(rcsv.readcsv(apair, ref m_remarks) == false)
				return false;
			if(rcsv.readcsv(apair, ref m_time) == false)
				return false;
			if(rcsv.readcsv(apair, ref m_count) == false)
				return false;
			return true;
		}
	}
	class tab_activity : ICsvRead, ICsv
	{
		/*********************************/
		public Int32		m_id;		// �id
		public string		m_name;		
		public string		m_remarks;		
		public EActivity		m_type;		// �����(1��������֮����<<��ļ���>>)
		public Int32		m_calendarid;		// �����Ľű�����
		/*********************************/
		public Int32 Id(){return m_id;}
		public bool Read(csvpair apair)
		{
			if(rcsv.readcsv(apair, ref m_id) == false)
				return false;
			if(rcsv.readcsv(apair, ref m_name) == false)
				return false;
			if(rcsv.readcsv(apair, ref m_remarks) == false)
				return false;
			Int32 lm_type = 0;
			if(rcsv.readcsv(apair, ref lm_type) == false)
				return false;
			m_type = (EActivity)lm_type;
			if(rcsv.readcsv(apair, ref m_calendarid) == false)
				return false;
			return true;
		}
	}
	class tab_activity_drawcompliance : ICsvRead, ICsv
	{
		/*********************************/
		public Int32		m_id;		// �ۼƴ���
		public string		m_name;		
		public string		m_remarks;		
		public Int32		m_dropid;		// ����id
		public Int32		m_mailid;		// �ʼ�id
		/*********************************/
		public Int32 Id(){return m_id;}
		public bool Read(csvpair apair)
		{
			if(rcsv.readcsv(apair, ref m_id) == false)
				return false;
			if(rcsv.readcsv(apair, ref m_name) == false)
				return false;
			if(rcsv.readcsv(apair, ref m_remarks) == false)
				return false;
			if(rcsv.readcsv(apair, ref m_dropid) == false)
				return false;
			if(rcsv.readcsv(apair, ref m_mailid) == false)
				return false;
			return true;
		}
	}
	class task_receive : ICsvRead
	{
		/*********************************/
		public ETask		m_receivetype;		// ETask(1.��ҵȼ��ﵽX 2.����vip�ȼ��ﵽx 3.���ĳID����)
		public List<Int32>		m_parmint = new List<Int32>();		
		/*********************************/
		public bool Read(csvpair apair)
		{
			Int32 lm_receivetype = 0;
			if(rcsv.readcsv(apair, ref lm_receivetype) == false)
				return false;
			m_receivetype = (ETask)lm_receivetype;
			if(rcsv.readcsv(apair, m_parmint) == false)
				return false;
			return true;
		}
	}
	class task_complete : ICsvRead
	{
		/*********************************/
		public ETask		m_completetype;		// ETask(1.��ҵȼ��ﵽX 2.����vip�ȼ��ﵽx 3.���ĳID����)
		public List<Int32>		m_parmint = new List<Int32>();		
		/*********************************/
		public bool Read(csvpair apair)
		{
			Int32 lm_completetype = 0;
			if(rcsv.readcsv(apair, ref lm_completetype) == false)
				return false;
			m_completetype = (ETask)lm_completetype;
			if(rcsv.readcsv(apair, m_parmint) == false)
				return false;
			return true;
		}
	}
	class tab_task : ICsvRead, ICsv
	{
		/*********************************/
		public Int32		m_id;		// ����id
		public string		m_name;		
		public string		m_remarks;		
		public ETaskType		m_type;		
		public Int32		m_dropid;		// ������
		public List<task_receive>		m_taskreceive = new List<task_receive>();		// ���մ������ǰ��
		public List<task_complete>		m_taskcomplete = new List<task_complete>();		// ��ɴ����������
		/*********************************/
		public Int32 Id(){return m_id;}
		public bool Read(csvpair apair)
		{
			if(rcsv.readcsv(apair, ref m_id) == false)
				return false;
			if(rcsv.readcsv(apair, ref m_name) == false)
				return false;
			if(rcsv.readcsv(apair, ref m_remarks) == false)
				return false;
			Int32 lm_type = 0;
			if(rcsv.readcsv(apair, ref lm_type) == false)
				return false;
			m_type = (ETaskType)lm_type;
			if(rcsv.readcsv(apair, ref m_dropid) == false)
				return false;
			if(rcsv.readcsv(apair, m_taskreceive) == false)
				return false;
			if(rcsv.readcsv(apair, m_taskcomplete) == false)
				return false;
			return true;
		}
	}
	class obstacles_data : ICsvRead
	{
		/*********************************/
		public List<eobstacles>		m_data = new List<eobstacles>();		
		/*********************************/
		public bool Read(csvpair apair)
		{
			if(rcsv.readcsv(apair, m_data) == false)
				return false;
			return true;
		}
	}
	class tab_map : ICsvRead, ICsv
	{
		/*********************************/
		public Int32		m_id;		// ��ͼid
		public string		m_name;		
		public string		m_remarks;		
		public Int32		m_w;		// x����
		public Int32		m_l;		// y�᳤��
		public Int32		m_nx;		// [��Ұ]x���������
		public Int32		m_ny;		// [��Ұ]y���������
		public Int32		m_obstaclenx;		// [Ѱ·]x���������
		public Int32		m_obstacleny;		// [Ѱ·]y���������
		public List<obstacles_data>		m_obstacles = new List<obstacles_data>();		// ��ͼ����
		/*********************************/
		public Int32 Id(){return m_id;}
		public bool Read(csvpair apair)
		{
			if(rcsv.readcsv(apair, ref m_id) == false)
				return false;
			if(rcsv.readcsv(apair, ref m_name) == false)
				return false;
			if(rcsv.readcsv(apair, ref m_remarks) == false)
				return false;
			if(rcsv.readcsv(apair, ref m_w) == false)
				return false;
			if(rcsv.readcsv(apair, ref m_l) == false)
				return false;
			if(rcsv.readcsv(apair, ref m_nx) == false)
				return false;
			if(rcsv.readcsv(apair, ref m_ny) == false)
				return false;
			if(rcsv.readcsv(apair, ref m_obstaclenx) == false)
				return false;
			if(rcsv.readcsv(apair, ref m_obstacleny) == false)
				return false;
			if(rcsv.readcsv(apair, m_obstacles) == false)
				return false;
			return true;
		}
	}
	class tab_matching : ICsvRead, ICsv
	{
		/*********************************/
		public Int32		m_id;		// �淨���� pbnet::eplays
		public string		m_name;		
		public string		m_remarks;		
		public Int32		m_count;		// �淨�ﵽ���������Կ����淨
		public Int32		m_time;		// ƥ���ʱ��
		public bool		m_iswaitconfirm;		// �Ƿ���Ҫ�ȴ�ȷ��
		public Int32		m_waitconfirmtime;		// �ȴ�ȷ�ϵ�ʱ��
		/*********************************/
		public Int32 Id(){return m_id;}
		public bool Read(csvpair apair)
		{
			if(rcsv.readcsv(apair, ref m_id) == false)
				return false;
			if(rcsv.readcsv(apair, ref m_name) == false)
				return false;
			if(rcsv.readcsv(apair, ref m_remarks) == false)
				return false;
			if(rcsv.readcsv(apair, ref m_count) == false)
				return false;
			if(rcsv.readcsv(apair, ref m_time) == false)
				return false;
			if(rcsv.readcsv(apair, ref m_iswaitconfirm) == false)
				return false;
			if(rcsv.readcsv(apair, ref m_waitconfirmtime) == false)
				return false;
			return true;
		}
	}
	class Vector2 : ICsvRead
	{
		/*********************************/
		public Int32		m_x;		
		public Int32		m_y;		
		/*********************************/
		public bool Read(csvpair apair)
		{
			if(rcsv.readcsv(apair, ref m_x) == false)
				return false;
			if(rcsv.readcsv(apair, ref m_y) == false)
				return false;
			return true;
		}
	}
	class tab_plays : ICsvRead, ICsv
	{
		/*********************************/
		public Int32		m_id;		// �淨
		public string		m_name;		
		public string		m_remarks;		
		public Int32		m_type;		// �淨���� pbnet::eplays
		public Int32		m_mapid;		// ���ĸ���ͼӦ�ø��淨
		public Int32		m_preparation_tm;		// ׼���׶�ʱ��
		public Int32		m_play_tm;		// �淨ʱ��
		public Int32		m_settlement_tm;		// ����ʱ��
		public List<Vector2>		m_birthpoint = new List<Vector2>();		// ������Vector2(m_x:int32_t,m_y:int32_t)	
		/*********************************/
		public Int32 Id(){return m_id;}
		public bool Read(csvpair apair)
		{
			if(rcsv.readcsv(apair, ref m_id) == false)
				return false;
			if(rcsv.readcsv(apair, ref m_name) == false)
				return false;
			if(rcsv.readcsv(apair, ref m_remarks) == false)
				return false;
			if(rcsv.readcsv(apair, ref m_type) == false)
				return false;
			if(rcsv.readcsv(apair, ref m_mapid) == false)
				return false;
			if(rcsv.readcsv(apair, ref m_preparation_tm) == false)
				return false;
			if(rcsv.readcsv(apair, ref m_play_tm) == false)
				return false;
			if(rcsv.readcsv(apair, ref m_settlement_tm) == false)
				return false;
			if(rcsv.readcsv(apair, m_birthpoint) == false)
				return false;
			return true;
		}
	}
	class tab_recharge : ICsvRead, ICsv
	{
		/*********************************/
		public Int32		m_id;		// ��ֵid
		public string		m_name;		
		public string		m_remarks;		
		public Int32		m_price;		// �۸�
		public Int32		m_gold;		// ��õĽ������
		public Int32		m_bonus;		// �����Ľ������
		public Int32		m_firstbonus;		// �׳佱���Ľ������
		public Int32		m_dropid;		// ����
		public Int32		m_vipexp;		// ��ֵ�õ�λ���͵�vip����
		public Int32		m_count;		// �Ƿ����Ƴ�ֵ����
		public List<Int32>		m_activityid = new List<Int32>();		// ����ָ�������ʱ���ܳ�ֵ��һ��
		/*********************************/
		public Int32 Id(){return m_id;}
		public bool Read(csvpair apair)
		{
			if(rcsv.readcsv(apair, ref m_id) == false)
				return false;
			if(rcsv.readcsv(apair, ref m_name) == false)
				return false;
			if(rcsv.readcsv(apair, ref m_remarks) == false)
				return false;
			if(rcsv.readcsv(apair, ref m_price) == false)
				return false;
			if(rcsv.readcsv(apair, ref m_gold) == false)
				return false;
			if(rcsv.readcsv(apair, ref m_bonus) == false)
				return false;
			if(rcsv.readcsv(apair, ref m_firstbonus) == false)
				return false;
			if(rcsv.readcsv(apair, ref m_dropid) == false)
				return false;
			if(rcsv.readcsv(apair, ref m_vipexp) == false)
				return false;
			if(rcsv.readcsv(apair, ref m_count) == false)
				return false;
			if(rcsv.readcsv(apair, m_activityid) == false)
				return false;
			return true;
		}
	}
}
