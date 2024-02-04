using System;
using System.IO;

namespace ngl
{
    enum ENUM_ACTOR
    {
        ACTOR_NONE = -1,
        //#######################  �ǵ���  #####################
        ACTOR_ROLE = 1,
        ACTOR_ROBOT,                                        // ������
        ACTOR_GUILD,                                        // ����	
        ACTOR_PLAYS,                                        // �淨
        ACTOR_PLAYS_GO_UNDERGROUNDPALACE = ACTOR_PLAYS,     // �淨[�´��ع�]

        //ACTOR_PLAYS_END = ACTOR_PLAYS + pbnet::eplays_count,
        //#######################  ����  #######################
        ACTOR_SIGNLE_START,
        ACTOR_ADDRESS_SERVER = ACTOR_SIGNLE_START,              // ���� actor address server  ����ַ���ַ������
        ACTOR_ADDRESS_CLIENT,                                   // ���� actor address client 
        ACTOR_LOGIN,
        ACTOR_GATEWAY,                                          // ����
        ACTOR_GATEWAY_CLIENT2GAME,                              // ���� [Client]->[Game]
        ACTOR_GATEWAY_GAME2CLIENT,                              // ���� [Game]	->[Client]
        ACTOR_CREATE,                                           // ��ָ��[Server]�ϴ���[Actor]
        ACTOR_LOG,
        ACTOR_MANAGE_ROLE,
        ACTOR_MANAGE_ROBOT,
        ACTOR_MANAGE_GUILD,                                     // ���������
        ACTOR_RELOADCSV,                                        // ���շַ�Ȼ������csv
        ACTOR_RELOADCSV_DISTRIBUTE,                             // �ַ�csv
        ACTOR_NOTICE,                                           // ����
        ACTOR_GM,                                               // GM
        ACTOR_MAIL,                                             // �ʼ�
        ACTOR_CHAT,                                             // ����
        ACTOR_RANKLIST,                                         // ���а�
        ACTOR_ACTIVITY_MANAGE,                                  // �����
        ACTOR_BRIEF,                                            // brief��Ҫ��Ϣ
        ACTOR_CROSS,                                            // ���
        ACTOR_CROSSDB,                                          // ������ݿ�
        ACTOR_CROSSCHAT,                                        // �������
        ACTOR_MANAGE_PLAYS,                                     // �����淨
        ACTOR_MATCHING,                                         // ƥ��
        ACTOR_DB,                                               // ���������һ��
        ACTOR_SIGNLE_FINISH = ACTOR_DB + Pbdb.ENUM_DB.Count,
        ACTOR_COUNT = ACTOR_SIGNLE_FINISH,
    }

    // actorΨһid(64bit)
    // 16λ			����ENUM_ACTOR
    // 16λ			����id	
    // 32λ			����id
    // ############ 64 bit ######### //
    // #actor_type###areaid###id#### //
    // #16bit########16bit####32bit# //
    class actor_guid
    {
        private Byte[] m_data   = new Byte[sizeof(Int64)];
              
        public static Int16 none_area()
        {
            return -1;
        }

        public static ENUM_ACTOR none_type()
        {
            return (ENUM_ACTOR)(-1);
        }

        public static Int32 none_actordataid()
        {
            return -1;
        }

        public actor_guid()
        {
        }

        public actor_guid(Int64 aid)
        {
            Buffer.BlockCopy(BitConverter.GetBytes(aid), 0, m_data, 0, sizeof(Int64));
        }

        public actor_guid(ENUM_ACTOR atype, Int16 aareaid, Int32 aid)
        {
            Int16 ltype = (Int16)atype;
            Buffer.BlockCopy(BitConverter.GetBytes(ltype) , 0, m_data, 0, sizeof(Int16));
            Buffer.BlockCopy(BitConverter.GetBytes(aareaid), 0, m_data, sizeof(Int16), sizeof(Int16));
            Buffer.BlockCopy(BitConverter.GetBytes(aid), 0, m_data, sizeof(Int32), sizeof(Int32));
        }

        // ��ȡguididֵ
        public Int64 id()
        {
            return BitConverter.ToInt64(m_data, 0);
        }

        // ��ȡENUM_ACTOR����
        public ENUM_ACTOR type()
        {
            return (ENUM_ACTOR)BitConverter.ToInt16(m_data, 0);
        }

        // ��ȡ����id
        public Int32 actordataid()
        {
            return BitConverter.ToInt32(m_data, sizeof(Int32));
        }

        // ��ȡ����
        public Int16 area()
        {
            return BitConverter.ToInt16(m_data, sizeof(Int16));
        }

        // �������͡�����������id����һ��i64_actorid
        public static Int64 make(ENUM_ACTOR atype, Int16 aareaid, Int32 aid)
        {
            actor_guid lguid = new actor_guid(atype, aareaid, aid);
            return lguid.id();
        }

        // �������͡�����id������Ϊnone_area()����һ��i64_actorid
        public static Int64 make(ENUM_ACTOR atype, Int32 aid)
        {
            actor_guid lguid = new actor_guid(atype, none_area(), aid);
            return lguid.id();
        }

        // �������͡�����idΪnone_actordataid()������Ϊnone_area()����һ��i64_actorid
        public static Int64 make(ENUM_ACTOR atype)
        {
            actor_guid lguid = new actor_guid(atype, none_area(), none_actordataid());
            return lguid.id();
        }

        // �������͡�����Ϊttab_servers::tab()->m_area none_actordataid()������idΪnone_actordataid����һ��i64_actorid
        public static Int64 make_self(ENUM_ACTOR atype)
        {
            //actor_guid lguid(atype, ttab_servers::tab()->m_area, none_actordataid());
            // return (i64_actorid)lguid;
            return 0;
        }

        // ��������none_type()������Ϊnone_area()����idΪnone_actordataid()����һ��i64_actorid
        public static Int64 make()
        {
            actor_guid lguid = new actor_guid(none_type(), none_area(), none_actordataid());
            return lguid.id();
        }

        // ### �滻type
        public static Int64 make_type(Int64 aactorid, ENUM_ACTOR atype)
        {
            actor_guid lguid1 = new actor_guid(aactorid);
            actor_guid lguid2 = new actor_guid(atype, lguid1.area(), lguid1.actordataid());
            return lguid2.id();
        }

        // ### �滻area
        public static Int64 make_area(Int64 aactorid, Int16 aareaid)
        {
            actor_guid lguid1 = new actor_guid(aactorid);
            actor_guid lguid2 = new actor_guid(lguid1.type(), aareaid, lguid1.actordataid());
            return lguid2.id();
        }

        // ### �滻actordataid
        public static Int64 make_actordataid(Int64 aactorid, Int32 aid)
        {
            actor_guid lguid1 = new actor_guid(aactorid);
            actor_guid lguid2 = new actor_guid(lguid1.type(), lguid1.area(), aid);
            return lguid2.id();
        }

        // ### �滻type
        public Int64 make_type(ENUM_ACTOR atype)
        {
            Int16 ltype = (Int16)atype;
            Buffer.BlockCopy(BitConverter.GetBytes(ltype), 0, m_data, 0, sizeof(Int16));
            return id();
        }

        // ### �滻area
        public Int64 make_area(Int16 aareaid)
        {
            Buffer.BlockCopy(BitConverter.GetBytes(aareaid), 0, m_data, sizeof(Int16), sizeof(Int16));
            return id();
        }

        // ### �滻actordataid
        public Int64 make_actordataid(Int32 aid)
        {
            Buffer.BlockCopy(BitConverter.GetBytes(aid), 0, m_data, sizeof(Int32), sizeof(Int32));
            return id();
        }

        // ### ��ȡactordataid
        public static Int32 actordataid(Int64 aactorid)
        {
            actor_guid lguid = new actor_guid(aactorid);
            return lguid.actordataid();
        }

        // ### ��ȡtype
        public static ENUM_ACTOR type(Int64 aactorid)
        {
            actor_guid lguid = new actor_guid(aactorid);
            return lguid.type();
        }

        // ### ��ȡarea
        public static Int16 area(Int64 aactorid)
        {
            actor_guid lguid = new actor_guid(aactorid);
            return lguid.area();
        }

        // sendmore ���͸�ͬ���͵�����actor
        public static Int64 moreactor(ENUM_ACTOR atype)
        {
            return make(atype, none_area(), none_actordataid());
        }

        // ���޲�make()һ��
        public static Int64 moreactor()
        {
            return make(none_type(), none_area(), none_actordataid());
        }

        // ���޲�make()һ��
        public void none()
        {
            Int16 ltype = (Int16)none_type();
            Buffer.BlockCopy(BitConverter.GetBytes(ltype), 0, m_data, 0, sizeof(Int16));
            Buffer.BlockCopy(BitConverter.GetBytes(none_area()), 0, m_data, sizeof(Int16), sizeof(Int16));
            Buffer.BlockCopy(BitConverter.GetBytes(none_actordataid()), 0, m_data, sizeof(Int32), sizeof(Int32));
        }

        public bool is_moreactor(ENUM_ACTOR atype)
        {
            actor_guid lguid = new actor_guid(atype, none_area(), none_actordataid());
            return id() == lguid.id();
        }

        // �Ƿ񷢸�ͬ���͵�����actor
        public static bool is_moreactor(Int64 actorid, ENUM_ACTOR atype)
        {
            actor_guid lguid = new actor_guid(actorid);
            return lguid.is_moreactor(atype);
        }

        // actor type �Ƿ���Ч
        public static bool is_actortypenone(Int64 actorid)
        {
            actor_guid lguid = new actor_guid(actorid);
            return lguid.is_actortypenone();
        }

        public bool is_actortypenone()
        {
            return type() == none_type();
        }

        //actor area �Ƿ���Ч
        public static bool is_actorareanone(Int64 actorid)
        {
            actor_guid lguid = new actor_guid(actorid);
            return lguid.is_actorareanone();
        }

        public bool is_actorareanone()
        {
            return area() == none_area();
        }

        //actor id �Ƿ���Ч
        public static bool is_actoridnone(Int64 actorid)
        {
            actor_guid lguid = new actor_guid(actorid);
            return lguid.is_actoridnone();
        }

        public bool is_actoridnone()
        {
            return actordataid() == none_actordataid();
        }

        public static bool is_single(ENUM_ACTOR atype)
        {
            return atype >= ENUM_ACTOR.ACTOR_SIGNLE_START && atype < ENUM_ACTOR.ACTOR_SIGNLE_FINISH;
        }
    }
}