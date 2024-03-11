## ��ι���һ��actor����
����actor����<br/>
��actor_roleΪ��<br/>
����Ҫ����actor���������<br/>
��ENUM_ACTOR�в����actor_role�����Ͷ���ACTOR_ROLE<br/>
```
enum ENUM_ACTOR
{
	ACTOR_NONE = -1,
	//#######################  �ǵ���  #####################
	ACTOR_ROLE = 1,
}
```
�ڹ��캯����ͨ��actorparmָ��actor����(type)������(area)������id(id)<br/>
�Ƿ���Ҫ��������(manage_dbclient) <br/>
Ȩ��(weight)�����������δ�����Ϣ������<br/>
�Ƿ�֧�ִ���㲥(broadcast)<br/>
```
actor_role::actor_role(i16_area aarea, i32_actordataid aroleid, void* adata) :
	actor(
		actorparm
		{
			.m_parm
			{
				.m_type = ACTOR_ROLE,
				.m_area = aarea,
				.m_id = aroleid,
				.m_manage_dbclient = true
			},
			.m_weight = 0x7fffffff,
			.m_broadcast = true,
		})
	, m_gatewayid(((actor_switch_process_role*)(adata))->m_gatewayid)
	, m_playactorid(0)
{
	assert(aarea == ttab_servers::tab()->m_area);
}
```
����������ָ��<br/>
m_typeҲ��������ΪACTOR_ROLE<br/>
m_areaҲ��������Ϊ���캯���Ĵ���aarea<br/>
m_idҲ��������idΪ���캯���Ĵ���aroleid<br/>
m_manage_dbclient��Ҫ��������<br/>
m_weightȨ��Ϊ���32λintֵ<br/>
m_broadcast֧�ֹ㲥��Ϣ�Ĵ���<br/>
ͬʱ��Ϊ����֧�������ݼ�������Ҫʵ���麯��init<br/>
```
virtual void init()
{
	m_info.set(this);
	m_bag.set(this);
	m_task.set(this);
}
```
������������dbclient�����ǵ�actor_role������й���<br/>
�������е����ݾͻ��Զ������ݿ��м��ص�dbclient��<br/>
�������ǻ���Ҫʵ��һ��ע�ắ��������ע��������Ҫ�������Ϣ<br/>
```
static void nregister()
{
	// ��ʱ��
	register_timer<actor_role>(&actor_role::timer_handle);
        // �Զ�����Ϣ����
	register_actor<EPROTOCOL_TYPE_CUSTOM, actor_role>(
		true
		, dregister_fun_handle(actor_role, actor_disconnect_close)
	);
        // protobuf��Ϣ����
	register_actor<EPROTOCOL_TYPE_PROTOCOLBUFF, actor_role>(
		true
		, dregister_fun_handle(actor_role, pbnet::PROBUFF_NET_ROLE_SYNC)
		, dregister_fun_handle(actor_role, pbnet::PROBUFF_NET_MATCHING_SUCCESS_RESPONSE)
		, dregister_fun_handle(actor_role, mforward<GM::PROBUFF_GM_RECHARGE>)
	);

	// ͨ�����ؽ���ת���Ŀͻ���Э��ע��
	nforward::c2g();
}
```
��������ע���˶Զ�ʱ���Ĵ���<br/>
����actor_role�еĶ�ʱ������д���ĵط���<br/>
��Ҫʵ��<br/>
```
bool actor_role::timer_handle(message<timerparm>& adata)
```
ͬʱ����Ҳע����<br/>
1.�Զ�����Ϣ�Ĵ���<br/>
2.protobuf��Ϣ����<br/>
3.ͨ�����ؽ���ת���Ŀͻ���Э��ע��<br/>
4.���Ƕ���Ҫʵ�����Ӧ����Ϣ����<br/>
```
// CMD Э��
bool handle(message<pbnet::PROBUFF_NET_CMD>& adata);
bool handle(message<pbnet::PROBUFF_NET_ROLE_SYNC>& adata);
bool handle(message<pbnet::PROBUFF_NET_GET_TIME>& adata);
bool handle(message<pbnet::PROBUFF_NET_SWITCH_LINE>& adata);
bool handle(message<actor_send_item>& adata);
bool handle(message<actor_disconnect_close>& adata);
//�淨�����ɹ�  ��¼�淨actorid
bool handle(message<pbnet::PROBUFF_NET_MATCHING_SUCCESS_RESPONSE>& adata);
bool handle(message<pbnet::PROBUFF_NET_RECHARGE>& adata);
bool handle(message<mforward<GM::PROBUFF_GM_RECHARGE>>& adata);
```
Ȼ���actor_role�����ͽ��й���<br/>
��void init_nactor_type()�����н��й���<br/>
```
dinit_atype(actor_role, ACTOR_ROLE);
```
ͬʱ�Զ�����ϢҲ��Ҫ�����Զ�����Э���<br/>
```
��void init_protobuf::init_customs()�м�����Ҫ�����Э��
init_customs(EPROTOCOL_TYPE_CUSTOM
	, null<timerparm>
);
�����˶�timerparm��Ϣ��֧��
```
