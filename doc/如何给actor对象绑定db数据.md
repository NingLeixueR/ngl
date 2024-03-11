## ��θ�actor�����db����
��actor_login����<br/>
1. ��db.proto�ļ��ж���Ҫ�洢�����ݽṹ�����Ӧ��ö��<br/>
```
enum ENUM_DB
{
	ENUM_DB_ACCOUNT = 0;		// �˺�����
	ENUM_DB_ROLE = 1;		// �������
	ENUM_DB_BRIEF = 2;		// ��Ҽ�Ҫ����
	ENUM_DB_BAG = 3;		// ��������
	ENUM_DB_KEYVALUE = 4;		// ��ֵ����
	ENUM_DB_MAIL = 5;		// �ʼ�����
	ENUM_DB_GUILD = 6;		// ��������
	ENUM_DB_NOTICE = 7;		// ��������
	ENUM_DB_RANKLIST = 8;		// ��������
	ENUM_DB_ACTIVITY = 9;		// �����
	ENUM_DB_TASK = 10;		// ��������
	ENUM_DB_COUNT = 11;
};
// ENUM_DB_ACCOUNT,				// �˺�����
message db_account
{
	optional int64	m_id			= 1;				// �ʺ�id
	optional int64	m_roleid		= 2;				// ��ɫid
	optional string m_account		= 3;				// �˺�
	optional string m_passworld		= 4;				// ����
	optional int32	m_area			= 5;				// ����id
}
```
2. �ں���[void init_protobuf::init_customs()]�ж�����а󶨣�<br/>
����֧���������л�<br/>
�Զ�����Э���<br/>
init_customs_db<pbdb::ENUM_DB_ACCOUNT, pbdb::db_account>();
3. ʵ��ndb_modular<>�������ݹ�����ĸ���<br/>
```
using account_db_modular = ndb_modular<
	EPROTOCOL_TYPE_PROTOCOLBUFF,  //���ݸ�ʽ  �˴�λprotobuf
	pbdb::ENUM_DB_ACCOUNT,        //�ն��������ö��
	pbdb::db_account,             //�ն�������ݽṹ
	actor_login                   //��󶨵�actor����
>;
```
4. �������ݹ�����account<br/>
```
class account : public account_db_modular
```
����<br/>
virtual void initdata();�������ݼ��سɹ��󱻵��ã����ǿ����ڴ˴������ݽ�������<br/>
virtual void set_id();����ָ�����õ����ݵ�id���˴�Ϊ-1��ʾ����ȫ������<br/>
<br/>
���ˡ�actor�����db���ݡ��������<br/>
���ʹ�ã���Ҫ�޸ġ�ʹ�á�ɾ�����ݾ���Ҫ����[ndb_modular](https://github.com/NingLeixueR/ngl/wiki/%E5%9F%BA%E6%9C%AC%E7%BB%93%E6%9E%84#ndb_modular)�����ṩ�ķ���

