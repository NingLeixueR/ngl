<?php
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: gm.proto

namespace GM;

use Google\Protobuf\Internal\GPBType;
use Google\Protobuf\Internal\RepeatedField;
use Google\Protobuf\Internal\GPBUtil;

/**
 * [请求]删除公告
 *
 * Generated from protobuf message <code>GM.PROBUFF_GM_DEL_NOTICE</code>
 */
class PROBUFF_GM_DEL_NOTICE extends \Google\Protobuf\Internal\Message
{
    /**
     * Generated from protobuf field <code>optional int64 m_id = 3;</code>
     */
    protected $m_id = null;

    /**
     * Constructor.
     *
     * @param array $data {
     *     Optional. Data for populating the Message object.
     *
     *     @type int|string $m_id
     * }
     */
    public function __construct($data = NULL) {
        \GPBMetadata\Gm::initOnce();
        parent::__construct($data);
    }

    /**
     * Generated from protobuf field <code>optional int64 m_id = 3;</code>
     * @return int|string
     */
    public function getMId()
    {
        return isset($this->m_id) ? $this->m_id : 0;
    }

    public function hasMId()
    {
        return isset($this->m_id);
    }

    public function clearMId()
    {
        unset($this->m_id);
    }

    /**
     * Generated from protobuf field <code>optional int64 m_id = 3;</code>
     * @param int|string $var
     * @return $this
     */
    public function setMId($var)
    {
        GPBUtil::checkInt64($var);
        $this->m_id = $var;

        return $this;
    }

}
