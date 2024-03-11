## ��θ�actor���������Ϣ
### actor ngl֧�ֵ���Ϣ����������
1. �Զ�����Ϣ����
2. protobuf��Ϣ
### �����Ƕԡ��Զ�����Ϣ���͡��Ľ���
1. ��nprotocol.h�ļ������Ƕ��Զ�����Ϣ���ж���
```
	struct nactornode
	{
		std::string		m_name;// ����������
		i32_serverid	m_serverid;// ������id
		std::vector<i16_actortype>	m_actortype;// ENUM_ACTOR_TYPE
		std::string		m_ip;// ip
		i16_port		m_port;// �˿�
		def_portocol_function(nactornode, m_name, m_serverid, m_actortype, m_ip, m_port)
	};

	// ---- [actor client -> actor server] register
	// ע����
	struct np_actornode_register
	{
		nactornode m_node;
		std::vector<i64_actorid> m_add;
		def_portocol(np_actornode_register, m_node, m_add)
	};
```
����np_actornode_register�ṹΪע�������Ϣ,nactornode���������Ľṹ<br/>
�����������ǳ���Ҫ�ĺ꣬����Ҫ�����ǰ󶨽ṹ��Ա�����������л�����֧��<br/>
def_portocol_function�����󶨷���Ϣ�ṹ,Ҳ������Ϣ�ṹ�ڰ����Ľṹ<br/>
def_portocol��������Ϣ�ṹ<br/>
2. ��Ҫ���Զ�����Ϣ�Զ����ɲ�����Э���
�ں���[void init_protobuf::init_customs()]�����
```
	init_customs(EPROTOCOL_TYPE_CUSTOM
		, null<timerparm>
		, null<np_robot_pram>
		, null<np_actornode_register>
	);
```
���˾��������actor�����ж���Դ���Ϣ��֧����,<br/>
��Ϊprotobuf��Ϣ���Զ�����Ϣ�Ĳ�����ͬ��<br/>
### �����Ƚ���protobuf�������������
1. ��net.proto�ļ��ж�����Ҫ֧�ֵ���Ϣ
2. Ȼ���Զ���������[makeproto.exe]�Զ�����net_protocol.xml��netserver_protocol.xml,
����Ҫ��Э��������Э��ŵ��Զ�����<br/>

### ��actor�ж���Ϣ��֧��
��actor�����ж����ʵ��bool handle(message<XXX>& adata);<br/>
����
```
bool handle(message<pbnet::PROBUFF_NET_SWITCH_LINE>& adata);
bool handle(message<np_actor_senditem>& adata);
```
��actor����ĺ���[static void nregister();]����ӶԺ�����ע��
```
register_actor<EPROTOCOL_TYPE_CUSTOM, actor_role>(
	true			// ����ָ���ǶԴ���Ϣ�Ĵ�����Ҫ��actor�������������ȫ�����غ�ſ�ʼ
	, dregister_fun_handle(actor_role, np_actor_senditem)
);
nforward::c2g();�����Ƕ�client��ϢҲ����protobuf��Ϣ�Ĵ������ע��,
��ΪgatewayҲ��Ҫע�����Զ�������˷�װ
```
