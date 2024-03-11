#pragma once

#include "ndb_modular.h"
#include "remakes.h"
#include "db.pb.h"
#include "itme.h"

namespace ngl
{
	struct autoitem;
	class actor_role;
	using bag_db_modular = ndb_modular<
		EPROTOCOL_TYPE_PROTOCOLBUFF, 
		pbdb::ENUM_DB_BAG,
		pbdb::db_bag,
		actor_role
	>;

	class bag :
		public bag_db_modular
	{
		std::map<int, pbdb::item*> m_stackitems;				// key tid 可堆叠的物品
		std::map<int, pbdb::item*> m_nostackitems;				// key id  不可堆叠的物品
		std::unique_ptr<autoitem> m_autoitem;
	public:
		bag();

		pbdb::db_bag& get_bag();

		const pbdb::db_bag& get_constbag();

		virtual void initdata();

		pbdb::item* add(pbdb::item& aitem);
	
		bool add_item(int32_t atid, int32_t acount);
		bool add_item(const std::map<int32_t, int32_t>& amap);
		bool add_item(std::vector<pbdb::item>& avec);

		// 只能删除可堆叠物品
		bool dec_item(int32_t atid, int32_t acount);
		// 删除不可堆叠物品
		bool dec_item(int32_t aid);
		
		bool checkbytid(int32_t atid, int32_t acount);
		bool checkbyid(int32_t aid);

		void sync_client();
	};
}// namespace ngl