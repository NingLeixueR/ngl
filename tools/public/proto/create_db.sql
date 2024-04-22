/*Date:2024-04-22 16:59:13.353*/

 DROP Database IF EXISTS `lbtest`;
 CREATE DATABASE lbtest default charset utf8 COLLATE utf8_general_ci;
 use lbtest;

-- ----------------------------
-- Table structure for db_account
-- ----------------------------
DROP TABLE IF EXISTS `db_account`;
CREATE TABLE `db_account` (
    `id` bigint(63) NOT NULL,
    `data` LongBlob,
    PRIMARY KEY(`id`)
)ENGINE = InnoDB DEFAULT CHARSET = utf8; 
-- ----------------------------
-- Table structure for db_brief
-- ----------------------------
DROP TABLE IF EXISTS `db_brief`;
CREATE TABLE `db_brief` (
    `id` bigint(63) NOT NULL,
    `data` LongBlob,
    PRIMARY KEY(`id`)
)ENGINE = InnoDB DEFAULT CHARSET = utf8; 
-- ----------------------------
-- Table structure for db_role
-- ----------------------------
DROP TABLE IF EXISTS `db_role`;
CREATE TABLE `db_role` (
    `id` bigint(63) NOT NULL,
    `data` LongBlob,
    PRIMARY KEY(`id`)
)ENGINE = InnoDB DEFAULT CHARSET = utf8; 
-- ----------------------------
-- Table structure for db_bag
-- ----------------------------
DROP TABLE IF EXISTS `db_bag`;
CREATE TABLE `db_bag` (
    `id` bigint(63) NOT NULL,
    `data` LongBlob,
    PRIMARY KEY(`id`)
)ENGINE = InnoDB DEFAULT CHARSET = utf8; 
-- ----------------------------
-- Table structure for db_keyvalue
-- ----------------------------
DROP TABLE IF EXISTS `db_keyvalue`;
CREATE TABLE `db_keyvalue` (
    `id` bigint(63) NOT NULL,
    `data` LongBlob,
    PRIMARY KEY(`id`)
)ENGINE = InnoDB DEFAULT CHARSET = utf8; 
-- ----------------------------
-- Table structure for db_mail
-- ----------------------------
DROP TABLE IF EXISTS `db_mail`;
CREATE TABLE `db_mail` (
    `id` bigint(63) NOT NULL,
    `data` LongBlob,
    PRIMARY KEY(`id`)
)ENGINE = InnoDB DEFAULT CHARSET = utf8; 
-- ----------------------------
-- Table structure for db_guild
-- ----------------------------
DROP TABLE IF EXISTS `db_guild`;
CREATE TABLE `db_guild` (
    `id` bigint(63) NOT NULL,
    `data` LongBlob,
    PRIMARY KEY(`id`)
)ENGINE = InnoDB DEFAULT CHARSET = utf8; 
-- ----------------------------
-- Table structure for db_notice
-- ----------------------------
DROP TABLE IF EXISTS `db_notice`;
CREATE TABLE `db_notice` (
    `id` bigint(63) NOT NULL,
    `data` LongBlob,
    PRIMARY KEY(`id`)
)ENGINE = InnoDB DEFAULT CHARSET = utf8; 
-- ----------------------------
-- Table structure for db_ranklist
-- ----------------------------
DROP TABLE IF EXISTS `db_ranklist`;
CREATE TABLE `db_ranklist` (
    `id` bigint(63) NOT NULL,
    `data` LongBlob,
    PRIMARY KEY(`id`)
)ENGINE = InnoDB DEFAULT CHARSET = utf8; 
-- ----------------------------
-- Table structure for db_activity
-- ----------------------------
DROP TABLE IF EXISTS `db_activity`;
CREATE TABLE `db_activity` (
    `id` bigint(63) NOT NULL,
    `data` LongBlob,
    PRIMARY KEY(`id`)
)ENGINE = InnoDB DEFAULT CHARSET = utf8; 
-- ----------------------------
-- Table structure for db_task
-- ----------------------------
DROP TABLE IF EXISTS `db_task`;
CREATE TABLE `db_task` (
    `id` bigint(63) NOT NULL,
    `data` LongBlob,
    PRIMARY KEY(`id`)
)ENGINE = InnoDB DEFAULT CHARSET = utf8; 
-- ----------------------------
-- Table structure for db_calendar
-- ----------------------------
DROP TABLE IF EXISTS `db_calendar`;
CREATE TABLE `db_calendar` (
    `id` bigint(63) NOT NULL,
    `data` LongBlob,
    PRIMARY KEY(`id`)
)ENGINE = InnoDB DEFAULT CHARSET = utf8; 
