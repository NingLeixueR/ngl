<?php
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: db.proto

namespace GPBMetadata;

class Db
{
    public static $is_initialized = false;

    public static function initOnce() {
        $pool = \Google\Protobuf\Internal\DescriptorPool::getGeneratedPool();

        if (static::$is_initialized == true) {
          return;
        }
        $pool->internalAddGeneratedFile(
            '
�
db.protopbdb"�

db_account
m_id (H �
m_roleid (H�
	m_account (	H�
m_passworld (	H�
m_area (H�B
_m_idB
	_m_roleidB

_m_accountB
_m_passworldB	
_m_area"�
db_brief
m_id (H �
m_name (	H�
m_lv (H�
m_moneygold (H�
m_moneysilver (H�B
_m_idB	
_m_nameB
_m_lvB
_m_moneygoldB
_m_moneysilver"U
db_role
m_id (H �#
m_base (2.pbdb.db_briefH�B
_m_idB	
_m_base"�
item
m_id (H �
m_tid (H�
m_count (H�
m_lv (H�
m_star (H�B
_m_idB
_m_tidB

_m_countB
_m_lvB	
_m_star"�
db_bag
m_id (H �)
m_items (2.pbdb.db_bag.MItemsEntry
m_maxid (H�9
MItemsEntry
key (
value (2
.pbdb.item:8B
_m_idB

_m_maxid"i
db_keyvalue
m_id (H �
m_key (	H�
m_value (	H�B
_m_idB
_m_keyB

_m_value"R
mailitem
	m_itemtid (H �
m_count (H�B

_m_itemtidB

_m_count"�
mail
m_id (H �
m_createutc (H�
m_tid (H�
m_prams (	H�
m_items (2.pbdb.mailitem
m_read (H�
m_draw (H�B
_m_idB
_m_createutcB
_m_tidB

_m_pramsB	
_m_readB	
_m_draw"�
db_mail
m_id (H �(
m_mail (2.pbdb.db_mail.MMailEntry8

MMailEntry
key (
value (2
.pbdb.mail:8B
_m_id"
db_guild
m_id (H �
m_guild (	H�
m_leader (H�
	m_members (B
_m_idB

_m_guildB
	_m_leader"�
	db_notice
m_id (H �
m_notice (	H�
m_starttime (H�
m_finishtime (H�B
_m_idB
	_m_noticeB
_m_starttimeB
_m_finishtime"�
rankitem
m_roleid (H �
m_name (	H�
m_lv (H�
m_lvtime (H�B
	_m_roleidB	
_m_nameB
_m_lvB
	_m_lvtime"�
db_ranklist
m_id (H �,
m_item (2.pbdb.db_ranklist.MItemEntry<

MItemEntry
key (
value (2.pbdb.rankitem:8B
_m_id"�
db_activity
m_id (H �\'
m_datas (2.pbdb.db_activity.data�
data
m_beg (H �
m_end (H�
m_start (H�
m_finish (H�E
m_drawcompliance (2+.pbdb.db_activity.data.MDrawcomplianceEntryD
drawcompliance
m_count (H �
m_reward (B

_m_count]
MDrawcomplianceEntry
key (4
value (2%.pbdb.db_activity.data.drawcompliance:8B
_m_begB
_m_endB

_m_startB
	_m_finishB
_m_id"�
db_task
m_id (H �#
m_datas (2.pbdb.db_task.data�
data
m_taskid (H �
m_receiveutc (H�

m_finshutc (H�

m_parmint1 (H�

m_parmint2 (H�
m_parmstring1 (	H�
m_parmstring2 (	H�B
	_m_taskidB
_m_receiveutcB
_m_finshutcB
_m_parmint1B
_m_parmint2B
_m_parmstring1B
_m_parmstring2B
_m_idBHbproto3'
        , true);

        static::$is_initialized = true;
    }
}

