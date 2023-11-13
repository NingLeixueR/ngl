#pragma once

#include "db.pb.h"
#include "itme.h"
#include "db_modular.h"
#include "remakes.h"

namespace ngl
{
	class temp_bag;
	class actor_role;
	using bag_db_modular = db_modular<
		EPROTOCOL_TYPE_PROTOCOLBUFF, 
		pbdb::ENUM_DB_BAG,
		pbdb::db_bag,
		actor_role
	>;
	class bag :
		public bag_db_modular
	{
		std::map<int, pbdb::item*> m_stackitems;				// key tid �ɶѵ�����Ʒ
		std::map<int, pbdb::item*> m_nostackitems;				// key id  ���ɶѵ�����Ʒ
	public:
		bag();

		pbdb::db_bag& get_bag();

		const pbdb::db_bag& get_constbag();

		virtual void initdata();

		pbdb::item* add(pbdb::item& aitem);
	
		bool add_item(int32_t atid, int32_t acount);
		bool add_item(const std::map<int32_t, int32_t>& amap);
		bool add_item(std::vector<pbdb::item>& avec);

		// ֻ��ɾ���ɶѵ���Ʒ
		bool dec_item(int32_t atid, int32_t acount);
		// ɾ�����ɶѵ���Ʒ
		bool dec_item(int32_t aid);

		bool checkbytid(int32_t atid, int32_t acount);
		bool checkbyid(int32_t aid);
	};

}