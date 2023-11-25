// ע�⡾rebuild.bat ���������ļ�����Ҫ�ֶ��޸ġ�
// ����ʱ�� // ����ʱ�� 23-11-25 20:38:24
#ifndef _csvtable_H_
#define _csvtable_H_
#include "actor_define.h"
#include "csv.h"
#include "csvpair.h"
#include "protocol_define.h"
#include "serialize.h"
namespace ngl{
enum ENET_CONFIG
{
	net_config_send_buff_maxbyte = 8129,	
	net_config_recv_buff_maxbyte = 8129,	
	net_config_logic_pthread_max_size = 8,	
	net_config_socket_pthread_max_size = 8,	
};
enum EUDP_OPERATOR
{
	EUDP_OPERATOR_ACK,	// ȷ�ϰ�
	EUDP_OPERATOR_DATA,	// ���������ݰ�
	EUDP_OPERATOR_HEARTBEAT,	// ������Ҫ����ȷ�϶Զ��Ƿ�����
};
enum EPH
{
	EPH_BYTES = 0,	// Э���ֽ���
	EPH_TIME,	// ���Ͷ˵�ʱ���
	EPH_PROTOCOLNUM,	// Э���
	EPH_PROTOCOLTYPE,	// Э������ EPROTOCOL_TYPE
	EPH_ACTOR_TYPEAREA,	// ACTOR_TYPE_AREA
	EPH_ACTOR_ID,	// ACTOR_ID
	EPH_REQUEST_ACTOR_TYPEAREA,	// Request REQUEST_ACTOR_TYPE_AREA
	EPH_REQUEST_ACTOR_ID,	// Request ACTOR_ID
	EPH_SUM,	
};
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
	FAIL = -1,	// ���������ʹ���
};
enum ENET_PROTOCOL
{
	ENET_TCP = 1,	
	ENET_UDP = 2,	
	ENET_WS = 3,	
};
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
};
enum EnumAttribute
{
	E_Null = 0,	
	E_Attack = 1,	// [����]
	E_Defense = 2,	// [����]
	E_Hp = 3,	// [Ѫ��]
	E_Anger = 4,	// [ŭ��]
	E_Speed = 5,	// [�ٶ�]
	E_Count = 6,	
};
enum EItemSrc
{
	EItemSrcNoraml = 0,	
	EItemSrcGM = 1,	
};
enum EItemConsume
{
	EItemConsumeNoraml = 0,	
	EItemConsumeGM = 1,	
};
enum EItemType
{
	EEquipment = 1,	// װ��
	EMaterial = 2,	// ����
	EMoneyGold = 3,	// ���
	EMoneySilver = 4,	// ����
	ECard = 5,	// ����
};
enum EQuality
{
	EQualityGrey = 0,	//��ɫ
	EQualityGreen = 1,	//��ɫ
	EQualityYellow = 2,	//��ɫ
	EQualityOrange = 3,	//��ɫ
	EQualityRed = 4,	//��ɫ
};
enum EEquip
{
	EEquipWeapon = 1,	// ����
	EEquipHelmet = 2,	// ͷ��
	EEquipCloth = 3,	// �·�
	EEquipPants = 4,	// ����
};
enum ECalendar
{
	Week = 0,	// �ܼ�
	ServerOpen = 1,	// �Կ���ʱ������������
	RegularSlot = 2,	// �̶�ʱ���
};
enum EActivity
{
	EActivityDrawCompliance = 1,	// ��������֮����<<��ļ���>>
};
enum ETask
{
	ETaskRoleLv = 1,	// ��ҵȼ�
	ETaskRoleVip = 2,	// ���vip�ȼ�
	ETaskTaskId = 3,	// ���ĳID����
};
enum ETaskType
{
	ETaskTypePrincipalLine,	// ��������
	ETaskTypeBranchLine,	// ֧������
	ETaskTypeDaily,	// ÿ������
};
enum eobstacles
{
	eobstacles_pass = 0,	// ����ͨ��
	eobstacles_nopass = 1,	// �޷�ͨ��
};
struct tab_servers
{
/*********************************/
	int32_t		m_id;		
	std::string		m_name;		
	std::string		m_remarks;		
	int16_t		m_area;		// ����
	NODE_TYPE		m_type;		// ����������(1db2actorserver3game4gateway5login6robot7world8log9reloadcsv10reloadcsv_tools)
	int32_t		m_tcount;		// ͬ���ͷ����������
	ENET_PROTOCOL		m_net;		// ������Э��(1tcp2udp3ws)
	std::string		m_ip;		// ip
	int16_t		m_port;		// �˿�
	int32_t		m_threadnum;		// socket�߳���
	int32_t		m_actorthreadnum;		// actor�̳߳��߳���
	bool		m_outernet;		// �Ƿ�������������
	int32_t		m_db;		// ���ӵ�db����id
	int32_t		m_reloadcsv;		// ���ӵ�reloadcsv����id
	int32_t		m_login;		// ���ӵ�login����id
	int16_t		m_crossarea;		// �������
	std::vector<int32_t>		m_actorserver;		// ���ӵ�actorserver����id(�����Ҫ��д���actorserver)
/*********************************/
	tab_servers();
	// ���л������л����
	def_portocol(tab_servers, m_id, m_name, m_remarks, m_area, m_type, m_tcount, m_net, m_ip, m_port, m_threadnum, m_actorthreadnum, m_outernet, m_db, m_reloadcsv, m_login, m_crossarea, m_actorserver)
	// csv���
	def_rcsv(m_id,m_name,m_remarks,m_area,m_type,m_tcount,m_net,m_ip,m_port,m_threadnum,m_actorthreadnum,m_outernet,m_db,m_reloadcsv,m_login,m_crossarea,m_actorserver)
};
struct tab_dbload
{
/*********************************/
	int32_t		m_id;		
	std::string		m_name;		
	std::string		m_remarks;		
	bool		m_isloadall;		// �Ƿ���Ҫ��������ȫ������
	bool		m_network;		// �Ƿ�����ͨ������ַ�
	int		m_sendmaxcount;		// ������෢������
/*********************************/
	tab_dbload();
	// ���л������л����
	def_portocol(tab_dbload, m_id, m_name, m_remarks, m_isloadall, m_network, m_sendmaxcount)
	// csv���
	def_rcsv(m_id,m_name,m_remarks,m_isloadall,m_network,m_sendmaxcount)
};
struct tab_errormessage
{
/*********************************/
	int32_t		m_id;		
	std::string		m_name;		
	std::string		m_remarks;		
	std::string		m_message;		// ��������
/*********************************/
	tab_errormessage();
	// ���л������л����
	def_portocol(tab_errormessage, m_id, m_name, m_remarks, m_message)
	// csv���
	def_rcsv(m_id,m_name,m_remarks,m_message)
};
struct tab_specialid
{
/*********************************/
	int32_t		m_id;		
	std::string		m_name;		
	std::string		m_remarks;		
	std::string		m_value;		
/*********************************/
	tab_specialid();
	// ���л������л����
	def_portocol(tab_specialid, m_id, m_name, m_remarks, m_value)
	// csv���
	def_rcsv(m_id,m_name,m_remarks,m_value)
};
struct tab_attribute
{
/*********************************/
	int32_t		m_id;		
	std::string		m_name;		
	std::string		m_remarks;		
	float		m_fightcoefficient;		// �����ṩ��ս��ϵ��
	int32_t		m_initvalue;		// ���Գ�ʼֵ
	int32_t		m_uplimit;		// ����
	int32_t		m_lowlimit;		// ����
/*********************************/
	tab_attribute();
	// ���л������л����
	def_portocol(tab_attribute, m_id, m_name, m_remarks, m_fightcoefficient, m_initvalue, m_uplimit, m_lowlimit)
	// csv���
	def_rcsv(m_id,m_name,m_remarks,m_fightcoefficient,m_initvalue,m_uplimit,m_lowlimit)
};
struct tab_item
{
/*********************************/
	int32_t		m_id;		
	std::string		m_name;		
	std::string		m_remarks;		
	int32_t		m_ranks;		// ����ֵ
	EItemType		m_type;		// ��Ʒ����EItemType(1װ��,2����,3���,4����)
	int32_t		m_quality;		// ��ƷƷ��(EQuality)
	bool		m_isstack;		// �Ƿ�ɶѵ�
/*********************************/
	tab_item();
	// ���л������л����
	def_portocol(tab_item, m_id, m_name, m_remarks, m_ranks, m_type, m_quality, m_isstack)
	// csv���
	def_rcsv(m_id,m_name,m_remarks,m_ranks,m_type,m_quality,m_isstack)
};
struct attributevalue
{
/*********************************/
	int32_t		m_id;		// ����id(EnumAttribute)
	bool		m_isratio;		// �Ƿ���ֱ�����
	int32_t		m_value;		// ����ֵ
/*********************************/
	attributevalue();
	// ���л������л����
	def_portocol(attributevalue, m_id, m_isratio, m_value)
	// csv���
	def_rcsv(m_id,m_isratio,m_value)
};
struct tab_equip
{
/*********************************/
	int32_t		m_id;		
	std::string		m_name;		
	std::string		m_remarks;		
	EEquip		m_position;		// ��λEEquip(1����2ͷ��3�·�4����)
	std::vector<attributevalue>		m_attributevalues;		// װ������
/*********************************/
	tab_equip();
	// ���л������л����
	def_portocol(tab_equip, m_id, m_name, m_remarks, m_position, m_attributevalues)
	// csv���
	def_rcsv(m_id,m_name,m_remarks,m_position,m_attributevalues)
};
struct tab_equiplv
{
/*********************************/
	int32_t		m_id;		
	std::string		m_name;		
	std::string		m_remarks;		
	int32_t		m_consume;		// ��������id
	std::vector<attributevalue>		m_attributevalues;		// װ������
/*********************************/
	tab_equiplv();
	// ���л������л����
	def_portocol(tab_equiplv, m_id, m_name, m_remarks, m_consume, m_attributevalues)
	// csv���
	def_rcsv(m_id,m_name,m_remarks,m_consume,m_attributevalues)
};
struct tab_card
{
/*********************************/
	int32_t		m_id;		
	std::string		m_name;		
	std::string		m_remarks;		
	EQuality		m_quality;		// Ʒ��EQuality(0��ɫ1��ɫ2��ɫ3��ɫ4��ɫ)
	std::vector<attributevalue>		m_attributevalues;		// ����
/*********************************/
	tab_card();
	// ���л������л����
	def_portocol(tab_card, m_id, m_name, m_remarks, m_quality, m_attributevalues)
	// csv���
	def_rcsv(m_id,m_name,m_remarks,m_quality,m_attributevalues)
};
struct trandom
{
/*********************************/
	int32_t		m_id;		
	int32_t		m_min;		
	int32_t		m_max;		
	int32_t		m_weight;		
/*********************************/
	trandom();
	// ���л������л����
	def_portocol(trandom, m_id, m_min, m_max, m_weight)
	// csv���
	def_rcsv(m_id,m_min,m_max,m_weight)
};
struct tab_random
{
/*********************************/
	int32_t		m_id;		
	std::string		m_name;		
	std::string		m_remarks;		
	bool		m_exclusive;		// �����Զ�ε���ʱʹ�ã�true���������ѵ�����Ʒ false�������ѵ�����Ʒ��
	int32_t		m_count;		// �������
	int32_t		m_calendarids;		// �Ƿ����������,ֻ�����������Ż�ִ�д˵���
	std::vector<trandom>		m_randomdatas;		// trandom(id*min*max*weight)
	std::vector<int32_t>		m_childrandomids;		// �����
/*********************************/
	tab_random();
	// ���л������л����
	def_portocol(tab_random, m_id, m_name, m_remarks, m_exclusive, m_count, m_calendarids, m_randomdatas, m_childrandomids)
	// csv���
	def_rcsv(m_id,m_name,m_remarks,m_exclusive,m_count,m_calendarids,m_randomdatas,m_childrandomids)
};
struct tconsume
{
/*********************************/
	int32_t		m_tid;		
	int32_t		m_count;		
/*********************************/
	tconsume();
	// ���л������л����
	def_portocol(tconsume, m_tid, m_count)
	// csv���
	def_rcsv(m_tid,m_count)
};
struct tab_consume
{
/*********************************/
	int32_t		m_id;		
	std::string		m_name;		
	std::string		m_remarks;		
	std::vector<tconsume>		m_consumeitems;		// tid*count
/*********************************/
	tab_consume();
	// ���л������л����
	def_portocol(tab_consume, m_id, m_name, m_remarks, m_consumeitems)
	// csv���
	def_rcsv(m_id,m_name,m_remarks,m_consumeitems)
};
struct tab_synthesis
{
/*********************************/
	int32_t		m_id;		
	std::string		m_name;		
	std::string		m_remarks;		
	int32_t		m_consume;		// �����б�
	int32_t		m_generate;		// �����(tab_rando)id ����ɹ���Ʒ�б�
/*********************************/
	tab_synthesis();
	// ���л������л����
	def_portocol(tab_synthesis, m_id, m_name, m_remarks, m_consume, m_generate)
	// csv���
	def_rcsv(m_id,m_name,m_remarks,m_consume,m_generate)
};
struct tweek
{
/*********************************/
	int32_t		m_week;		// �ܼ�
	std::string		m_opentime;		//  ����ʱ�� HH:mm:ss
	std::string		m_closetime;		//  ����ʱ�� HH:mm:ss
/*********************************/
	tweek();
	// ���л������л����
	def_portocol(tweek, m_week, m_opentime, m_closetime)
	// csv���
	def_rcsv(m_week,m_opentime,m_closetime)
};
struct tserveropen
{
/*********************************/
	int32_t		m_beg;		// ����������쿪��
	std::string		m_opentime;		// ����ʱ�� HH:mm:ss
	int32_t		m_end;		// ��������������
	std::string		m_closetime;		// ����ʱ�� HH:mm:ss
/*********************************/
	tserveropen();
	// ���л������л����
	def_portocol(tserveropen, m_beg, m_opentime, m_end, m_closetime)
	// csv���
	def_rcsv(m_beg,m_opentime,m_end,m_closetime)
};
struct tregularslot
{
/*********************************/
	std::string		m_opentime;		// ����ʱ�� YYYY-MM-DD HH:mm:ss
	std::string		m_closetime;		// ����ʱ�� YYYY-MM-DD HH:mm:ss
/*********************************/
	tregularslot();
	// ���л������л����
	def_portocol(tregularslot, m_opentime, m_closetime)
	// csv���
	def_rcsv(m_opentime,m_closetime)
};
struct tab_calendar
{
/*********************************/
	int32_t		m_id;		
	std::string		m_name;		
	std::string		m_remarks;		
	ECalendar		m_type;		//ECalendar(0:�ܼ�,1:�Կ���ʱ������������,2:�̶�ʱ���)
	std::vector<tweek>		m_week;		//m_type=0,tweek(�ܼ�(1-7)*����ʱ��HH:mm:ss*����ʱ��HH:mm:ss)
	std::vector<tserveropen>		m_serveropen;		//m_type=1,tserveropen(����������쿪��*����ʱ��HH:mm:ss*��������������*����ʱ��HH:mm:ss)
	std::vector<tregularslot>		m_tregularslot;		//m_type=2,tregularslot(����ʱ��YYYY/MM/DD HH:mm:ss*����ʱ��YYYY/MM/DD HH:mm:ss)
/*********************************/
	tab_calendar();
	// ���л������л����
	def_portocol(tab_calendar, m_id, m_name, m_remarks, m_type, m_week, m_serveropen, m_tregularslot)
	// csv���
	def_rcsv(m_id,m_name,m_remarks,m_type,m_week,m_serveropen,m_tregularslot)
};
struct tab_mail
{
/*********************************/
	int32_t		m_id;		
	std::string		m_name;		
	std::string		m_remarks;		
	std::string		m_title;		// �ʼ�����
	std::string		m_author;		// �ʼ�����
	std::string		m_content;		// �ʼ�����
/*********************************/
	tab_mail();
	// ���л������л����
	def_portocol(tab_mail, m_id, m_name, m_remarks, m_title, m_author, m_content)
	// csv���
	def_rcsv(m_id,m_name,m_remarks,m_title,m_author,m_content)
};
struct tab_chat
{
/*********************************/
	int32_t		m_id;		
	std::string		m_name;		
	std::string		m_remarks;		
	int32_t		m_time;		// ���췢�Լ��
	int32_t		m_count;		// ���췢���������
/*********************************/
	tab_chat();
	// ���л������л����
	def_portocol(tab_chat, m_id, m_name, m_remarks, m_time, m_count)
	// csv���
	def_rcsv(m_id,m_name,m_remarks,m_time,m_count)
};
struct tab_activity
{
/*********************************/
	int32_t		m_id;		// �id
	std::string		m_name;		
	std::string		m_remarks;		
	EActivity		m_type;		// �����(1��������֮����<<��ļ���>>)
	int32_t		m_calendarid;		// �����Ľű�����
/*********************************/
	tab_activity();
	// ���л������л����
	def_portocol(tab_activity, m_id, m_name, m_remarks, m_type, m_calendarid)
	// csv���
	def_rcsv(m_id,m_name,m_remarks,m_type,m_calendarid)
};
struct tab_activity_drawcompliance
{
/*********************************/
	int32_t		m_id;		// �ۼƴ���
	std::string		m_name;		
	std::string		m_remarks;		
	int32_t		m_dropid;		// ����id
	int32_t		m_mailid;		// �ʼ�id
/*********************************/
	tab_activity_drawcompliance();
	// ���л������л����
	def_portocol(tab_activity_drawcompliance, m_id, m_name, m_remarks, m_dropid, m_mailid)
	// csv���
	def_rcsv(m_id,m_name,m_remarks,m_dropid,m_mailid)
};
struct task_receive
{
/*********************************/
	ETask		m_receivetype;		// ETask(1.��ҵȼ��ﵽX 2.����vip�ȼ��ﵽx 3.���ĳID����)
	std::vector<int32_t>		m_parmint;		
/*********************************/
	task_receive();
	// ���л������л����
	def_portocol(task_receive, m_receivetype, m_parmint)
	// csv���
	def_rcsv(m_receivetype,m_parmint)
};
struct task_complete
{
/*********************************/
	ETask		m_completetype;		// ETask(1.��ҵȼ��ﵽX 2.����vip�ȼ��ﵽx 3.���ĳID����)
	std::vector<int32_t>		m_parmint;		
/*********************************/
	task_complete();
	// ���л������л����
	def_portocol(task_complete, m_completetype, m_parmint)
	// csv���
	def_rcsv(m_completetype,m_parmint)
};
struct tab_task
{
/*********************************/
	int32_t		m_id;		// ����id
	std::string		m_name;		
	std::string		m_remarks;		
	ETaskType		m_type;		
	int32_t		m_dropid;		// ������
	std::vector<task_receive>		m_taskreceive;		// ���մ������ǰ��
	std::vector<task_complete>		m_taskcomplete;		// ��ɴ����������
/*********************************/
	tab_task();
	// ���л������л����
	def_portocol(tab_task, m_id, m_name, m_remarks, m_type, m_dropid, m_taskreceive, m_taskcomplete)
	// csv���
	def_rcsv(m_id,m_name,m_remarks,m_type,m_dropid,m_taskreceive,m_taskcomplete)
};
struct obstacles_data
{
/*********************************/
	std::vector<eobstacles>		m_data;		
/*********************************/
	obstacles_data();
	// ���л������л����
	def_portocol(obstacles_data, m_data)
	// csv���
	def_rcsv(m_data)
};
struct tab_map
{
/*********************************/
	int32_t		m_id;		// ��ͼid
	std::string		m_name;		
	std::string		m_remarks;		
	int32_t		m_w;		// x����
	int32_t		m_l;		// y�᳤��
	int32_t		m_nx;		// [��Ұ]x���������
	int32_t		m_ny;		// [��Ұ]y���������
	int32_t		m_obstaclenx;		// [Ѱ·]x���������
	int32_t		m_obstacleny;		// [Ѱ·]y���������
	std::vector<obstacles_data>		m_obstacles;		// ��ͼ����
/*********************************/
	tab_map();
	// ���л������л����
	def_portocol(tab_map, m_id, m_name, m_remarks, m_w, m_l, m_nx, m_ny, m_obstaclenx, m_obstacleny, m_obstacles)
	// csv���
	def_rcsv(m_id,m_name,m_remarks,m_w,m_l,m_nx,m_ny,m_obstaclenx,m_obstacleny,m_obstacles)
};
struct tab_matching
{
/*********************************/
	int32_t		m_id;		// �淨���� pbnet::eplays
	std::string		m_name;		
	std::string		m_remarks;		
	int32_t		m_count;		// �淨�ﵽ���������Կ����淨
	int32_t		m_time;		// ƥ���ʱ��
	bool		m_iswaitconfirm;		// �Ƿ���Ҫ�ȴ�ȷ��
	int32_t		m_waitconfirmtime;		// �ȴ�ȷ�ϵ�ʱ��
/*********************************/
	tab_matching();
	// ���л������л����
	def_portocol(tab_matching, m_id, m_name, m_remarks, m_count, m_time, m_iswaitconfirm, m_waitconfirmtime)
	// csv���
	def_rcsv(m_id,m_name,m_remarks,m_count,m_time,m_iswaitconfirm,m_waitconfirmtime)
};
struct tab_playes
{
/*********************************/
	int32_t		m_id;		// �淨
	std::string		m_name;		
	std::string		m_remarks;		
	int32_t		m_type;		// �淨���� pbnet::eplays
	int32_t		m_mapid;		// ���ĸ���ͼӦ�ø��淨
	int32_t		m_preparation_tm;		// ׼���׶�ʱ��
	int32_t		m_play_tm;		// �淨ʱ��
	int32_t		m_settlement_tm;		// ����ʱ��
/*********************************/
	tab_playes();
	// ���л������л����
	def_portocol(tab_playes, m_id, m_name, m_remarks, m_type, m_mapid, m_preparation_tm, m_play_tm, m_settlement_tm)
	// csv���
	def_rcsv(m_id,m_name,m_remarks,m_type,m_mapid,m_preparation_tm,m_play_tm,m_settlement_tm)
};
}//namespace ngl
#endif //_csvtable_H_
