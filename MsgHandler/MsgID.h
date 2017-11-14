#ifndef _ASSS_MSGID_H_
#define _ASSS_MSGID_H_

#include "Config.h"

namespace REQ
{
    //聊天

    const UInt8 CHAT                 = 0x06;
    //强化

    const UInt8 SIGN                 =0x10;
    const UInt8 SIGN_INFO            =0x11;

    const UInt8 ENCHART              = 0x20;// 0xF0
    const UInt8 ENCHARTSOLDIER       = 0x21;// 0xF0

    /*背包信息*/
    const UInt8 PACKAGE_INFO         = 0x30;// 0xE0

    /*刷将*/
    const UInt8 FIND_FIGHTER         = 0x31;// 0xE1
    const UInt8 FIND_INFO         = 0x32;// 0xE1

    const UInt8 UP_FIGHTER          =0x33;
    
    /**战报请求 */
    const UInt8 BATTLE_REPORT_REQ    = 0x80;// 0xC0
    const UInt8 BATTLE_REPORT_REQ1   = 0x81;// 0xC0

    const UInt8 BATTLE_ARENA   = 0x83;// 0xC0
    /**登陆 */
    const UInt8 LOGIN               = 0xE0;// 0x10
    /**创建角色 */
    const UInt8 CREATE_ROLE         = 0xE1;// 0x11
    /**新手引导步骤 */
    const UInt8 NEW_HAND_STEP       = 0xE3;// 0x13
    /**请求玩家信息 */
    const UInt8 USER_INFO           = 0xE4;// 0x14
    /**BUFFER信息改变 */
    //创建帐号
    const UInt8 CREATE_ACCOUNT      = 0xE5;// 0x15

    const UInt8 IDENTIFY_ACCOUNT    = 0xE6;// 0x15

    const UInt8 GMHAND              = 0xEF;
    
    /*好友列表请求*/
    const UInt8 FRIEND_LIST         = 0x40;
    /*好友查找*/
    const UInt8 FRIEND_FIND         = 0x41; //
    /*好友申请*/
    const UInt8 FRIEND_APPLY        = 0x42;
    /*好友添加*/
    const UInt8 FRIEND_ADD          = 0x43;
    /*好友删除*/
    const UInt8 FRIEND_DELETE       = 0x44;
    /*好友推荐*/
    const UInt8 FRIEND_RECOMMAND    = 0x45;
    /*好友基础信息*/
    const UInt8 FRIEND_BASEINFO     = 0x46;


    //Mail
    const UInt8 MAIL                = 0x50;// 
    const UInt8 MAIL_GET            = 0x51;// 
    const UInt8 MAIL_DELETE         = 0x52;// 
    const UInt8 MAIL_NOTICE         = 0x52;// 
    const UInt8 MAIL_GET_ALL        = 0x53;// 
    const UInt8 MAIL_DELETE_ALL     = 0x54;// 

    const UInt8 CLAN_LIST           = 0x70;
    const UInt8 CLAN_CREATE         = 0x71;
    //const UInt8 CLAN_FLASH        = 0x72;
    const UInt8 CLAN_INFO           = 0x72;
    const UInt8 CLAN_OPTION         = 0x73;
    const UInt8 CLAN_APPLY          = 0x74;
    const UInt8 CLAN_LEAVE          = 0x75;


    /*治理换将*/
    const UInt8 GOVERN_REPLACE      = 0x60;
    /*离线治理获得*/
    const UInt8 GOVERN_OFFLIEN_GAIN = 0x61;
    /*治理加速*/
    const UInt8 GOVERN_SPEEDUP      = 0x62;
    /*请求治理信息*/
    const UInt8 GOVERN_INFO         = 0x63;
    /*在线治理获得*/
    const UInt8 GOVERN_ONLINE_GAIN  = 0x64;

    /*推图战役奖励*/
    const UInt8 BATTLE_AWARD        = 0x82;



    /*军团战报名*/
    const UInt8 CLAN_BATTLE_JOIN          = 0xA0;
    /*军团战加战将*/
    const UInt8 CLAN_BATTLE_ADDFIGHTER    = 0xA1;
    /*军团战移动战将*/
    const UInt8 CLAN_BATTLE_MOVEFIGHTER   = 0xA2;
    /*取消放置战将*/
    const UInt8 CLAN_BATTLE_CANCELFIGHTER = 0xA3;
    /*军团令*/
    const UInt8 CLAN_BATTLE_ORDERS        = 0xA4;
    /*留言*/
    const UInt8 CLAN_BATTLE_COMMENTS      = 0xA5;
    /*请求战报*/
    const UInt8 CLAN_BATTLE_REPORT        = 0xA6;
    /*战场信息*/
    const UInt8 CLAN_BATTLE_INFO          = 0xA7;
    /*战报回放*/
    const UInt8 CLAN_BATTLE_REPORTList    = 0xA8;
    /*战绩排行*/
    const UInt8 CLAN_BATTLE_RANK          = 0xA9;
    /*战绩信息*/
    const UInt8 CLAN_BATTLE_RESULTINFO    = 0xAA;
    /*战场个人战况*/
    const UInt8 CLAN_BATTLE_SELFINFO      = 0xAB;
    /*战役过程*/
    const UInt8 CLAN_BATTLE_PROCESS       = 0xAC;


    /*开采换将*/
    const UInt8 EXPLOIT_REPLACE_FIGHTER   = 0xB0;
    /*资源采集*/
    const UInt8 EXPLOIT_COLLECT           = 0xB1;
    /*开采加速*/
    const UInt8 EXPLOIT_SPEEDUP           = 0xB2;


    /*商城系统*/
    /*商城信息*/
    const UInt8 STOREA_INFO               = 0xC0;
    /*商城购买刷新*/
    const UInt8 STOREA_FRESH              = 0xC1;
    /*商城物品购买*/
    const UInt8 STOREA_BUY                = 0xC2;







    /**保持连接 */
    const UInt8 KEEP_ALIVE          = 0x00;
    /**自动重连 */
    const UInt8 RECONNECT           = 0x01;
    /**剑侠秘箓领取奖励 */
    const UInt8 HEROMEMO            = 0x06;
    /**密友奖励领取 */
    const UInt8 CFRIEND             = 0x07;
    /**离线经验领取 */
    const UInt8 OFFLINEEXP          = 0x08;
    /**代币使用 */
    const UInt8 TOKEN               = 0x09;
    /**领取出生七天奖励 */
    const UInt8 RC7DAY              = 0x0B;
    /**发表说说奖励 */
    const UInt8 SSAWARD             = 0x0C;
    /**使用灵气 */
    const UInt8 USESOUL             = 0x0D;
    /**服务器当前状态 */
    const UInt8 SVRST               = 0x11;
    /**领取蓝黄钻之力 */
    const UInt8 YBBUF               = 0x12;
    /**领取奖励 */
    const UInt8 GETAWARD            = 0x13;
    /**寻宝排行榜 */
    const UInt8 LUCKY_RANK          = 0x14;
    /** 各种活动 **/
    const UInt8 COUNTRY_ACT         = 0x1B;
    /** 新版出生七天活动 */
    const UInt8 NEWRC7DAY           = 0x1C;
    /** 墨家面板协议 */
    const UInt8 EXJOB               = 0x1D;
    /** 墨家游戏协议 */
    const UInt8 JOBHUNTER           = 0x1E;
    /** 自动寻墨游戏 */
    const UInt8 AUTOJOBHUNTER       = 0X2A;
    /** 水晶梦境协议 */
    const UInt8 DREAMER             = 0x29;
    /**成就 */
    const UInt8 ACHIEVEMENT         = 0xF0;// 0x0C
    /**阵营选择 */
    const UInt8 CAMPS_CHOICE        = 0xF1;// 0x0D
    /**回流用户7日活动指令 */
    const UInt8 RF7DAY              = 0x15;
    /** ??? */
    const UInt8 STATE_CHANGE        = 0x16;
    /**查询书商 */
    const UInt8 BOOK_LIST           = 0xEC;// 0x1A
    /**买书 */
    const UInt8 BOOK_BUY            = 0xED;// 0x1B
    /**读阵型 */
    const UInt8 READ_BATTLE         = 0xEE;// 0x1D
    /**改变阵型 */
    const UInt8 BATTLE_CHECK        = 0xEF;// 0x1E
    /**装备改变 */
    const UInt8 CHANGE_EQ           = 0xD0;// 0x21
    /**雇用散仙 */
    const UInt8 HIRE_HERO           = 0xD1;// 0x22
    /**散仙信息 */
    const UInt8 HERO_INFO           = 0xD2;// 0x23
    /**酒馆列表 */
    const UInt8 HOTEL_LIST          = 0xD3;// 0x26
    /**解雇散仙 */
    const UInt8 FIRE_HERO           = 0xD4;// 0x27
    /**接收散仙 */
    const UInt8 ACCEPT_FIGHTER      = 0xD5;// 0x28
    /**对某人使用物品 */
    const UInt8 PACK_USE_OTHER      = 0xD7;//
    /**加血 */
    const UInt8 ADD_HP              = 0xDE;// 0x29
    /**潜力洗炼 */
    const UInt8 POTENTIAL           = 0xDF;// 0x2C
    /**请求修炼武将列表 */
    //const UInt8 TRAIN_FIGHTER_LIST  = 0x2D;
    /**加速取消修炼散仙 */
    const UInt8 TRAIN_FIGHTER_OP    = 0x37;
    /**背包列表信息 */
    const UInt8 PACK_INFO           = 0xC0;// 0x30
    /**临时物品信息 */
    const UInt8 TEMPITEM_INFO       = 0xFA;
    /**墨方信息*/
    const UInt8 MOFANG_INFO         = 0xFB;
    /**背包添加到九疑鼎 */
    const UInt8 PACK_TRIPOD         = 0xC1;// 0x31
    /**背包卖出 */
    const UInt8 PACK_SELL           = 0xC2;// 0x32
    /**背包使用 */
    const UInt8 PACK_USE            = 0xC3;// 0x33
    /**背包扩展 */
    const UInt8 PACK_EXTEND         = 0xC4;// 0x34
    /**在线奖励 */
    const UInt8 REWARD              = 0xCF;// 0x38
    /**九疑鼎 */
    const UInt8 TRIPOD_INFO         = 0xCE;// 0x39
    /**探险信息 */
    const UInt8 LUCKYDRAW_INFO      = 0x3D;
    /**探险 */
    const UInt8 LUCKYDRAW           = 0x3E;
    /**装备强化 */
    const UInt8 EQ_ENHANCE          = 0xB0;// 0x40
    /**装备打孔 */
    const UInt8 EQ_PUNCH            = 0xB1;// 0x41
    /**宝石镶嵌 */
    const UInt8 EQ_EMBED            = 0xB2;// 0x43
    /**宝石拆卸 */
    const UInt8 EQ_UN_EMBED         = 0xB3;// 0x44
    /**单个分解 */
    const UInt8 EQ_UN_SINGLE        = 0x45;
    /**转换装备 */
    const UInt8 EQ_EXCHANGE         = 0x46;
    /**装备洗炼 */
    const UInt8 EQ_PURIFY           = 0xB4;// 0x47
    /**批量分解 */
    const UInt8 EQ_DECOMPOSE        = 0xB5;// 0x49
    /**置换部位 */
    const UInt8 EQ_EXCHANGE_POS     = 0x4A;
    /**宝石批量合成 */
    const UInt8 GEM_UPGRADE         = 0xB6;// 0x4B
    /**装备激活 */
    const UInt8 EQ_ACTIVE           = 0x4C;
    /**地图获取据点信息 */
    const UInt8 MAP_LOCATE          = 0xA0;// 0x51
    /**地图传送 */
    const UInt8 MAP_TRANSPORT       = 0xA1;// 0x52
    /**坐骑系统 */
    const UInt8 MODIFY_MOUNT         = 0xAA;// 0x58
    /**请求通天塔信息 */
    const UInt8 BABEL_UPDATE        = 0xAB;// 0x59
    /**开始通天塔战斗 */
    const UInt8 BABEL_START         = 0xAC;// 0x5A
    /**开始自动通天塔战斗 */
    const UInt8 BABEL_AUTO_START    = 0xAD;// 0x5B
    /**立即完成通天塔战斗 */
    const UInt8 BABEL_END           = 0xAE;// 0x5C
    /**日常 */
    const UInt8 DAILY               = 0xAF;// 0x5F
    /**换名字 */
    //const UInt8 CHANGE_NAME         = 0x60;
    /**加入国战 */
    const UInt8 CAMPS_WAR_JOIN      = 0x90;// 0x62
    /**请求国战信息 */
    const UInt8 CAMPS_WAR_INFO      = 0x91;
    /**加入新国战 */
    const UInt8 NEW_CAMPS_WAR_JOIN  = 0x2B;
    /**副本数据 */
    const UInt8 COPY_DATA           = 0x94;// 0x67
    /**阵图数据 */
    const UInt8 FORMATION_DATA      = 0x95;// 0x68
    /**自动副本 */
    const UInt8 AUTO_COPY           = 0x96;// ??
    /**自动阵图 */
    const UInt8 AUTO_FRONTMAP       = 0x98;// ??
    /**请求战报 */
    const UInt8 FIGHT_REPORT        = 0x9A;// 0x6C
    /**打怪 */
    //const UInt8 ATTACK_NPC          = 0x9B;// 0x61
    /**挂机 */
    const UInt8 TASK_HOOK           = 0x9D;// 0x6D
    /**挂机停止 */
    const UInt8 TASK_HOOK_STOP      = 0x9E;// 0x6E
    /**挂机加速 */
    const UInt8 TASK_HOOK_ADD       = 0x9F;// 0x6F
    /**妖王再临 */
    //const UInt8 ERLKING_INFO        = 0x71;
    /**发起切磋请求 */
    const UInt8 LANCHCHALLENGE      = 0x72;
    /**回复切磋 */
    const UInt8 REQUESTCHALLENGE    = 0x73;
    /**结婚面板*/
    const UInt8 MARRYBOARD          = 0x74;
    /**战斗退出 */
    const UInt8 FIGHT_EXIT          = 0x9C;// 0x77
    /**帮派战 */
    const UInt8 CLAN_BATTLE         = 0x79;
    /** */
    const UInt8 CLANCITYBATTLELIST  = 0x7A;
    /**帮派动态信息 */
    //const UInt8 CLAN_INFO           = 0x7C;
    /**获取战报信息请求 */
    //const UInt8 CLAN_BATTLE_INFO    = 0x7D;
    /**点击NPC对话 */
    const UInt8 DIALOG_START        = 0x50;// 0x80
    /**点击交互动作 */
    const UInt8 NPC_INTERACT        = 0x51;// 0x81
    /**当前任务列表请求 */
    const UInt8 CURR_TASK_LIST      = 0x52;// 0x82
    /**当前可接任务列表请求 */
    const UInt8 CURR_AVAILABLE_TASK = 0x53;// 0x83
    /**玩家接受、提交、放弃某任务请求 */
    const UInt8 TASK_ACTION         = 0x54;// 0x85
    /**护送任务玩家到达可触发战斗据点 */
    const UInt8 CONVEYBATTLE        = 0x88;
    /**采集任务物品请求 */
    const UInt8 COLLECTNPCACTION    = 0x89;
    /**循环任务刷新 */
    const UInt8 TASK_CYC_REFRESH    = 0x57;// 0x8B
    /**活动指令 */
    const UInt8 ACT                 = 0x8B;
    /**自动完成日常任务 */
    const UInt8 DAYTASKAUTOCOMPLETED= 0x8C;
    /**??? */
    const UInt8 AUTO_COMPLETED_TASK = 0x8D;
    /**循环任务进度请求 */
    const UInt8 QUERYDAYTASK        = 0x8F;
    /**请求帮派列表信息 */
    const UInt8 _CLAN_LIST           = 0x60;// 0x90
    /**请求自己帮派信息 */
    //const UInt8 CLAN_SELF           = 0x61;// 0x91
    /**帮派创建 */
    //const UInt8 CLAN_CREATE         = 0x62;// 0x92
    /**申请加入帮派 */
    //const UInt8 CLAN_APPLY          = 0x63;// 0x93
    /**帮派成员操作 */
    const UInt8 CLAN_OPERATE        = 0x64;// 0x94
    /**帮派信息改变 */
    const UInt8 CLAN_INFO_CHANGE    = 0x65;// 0x95
    /**请求某个帮派信息 */
    const UInt8 CLAN_REQ_OTHER      = 0x66;// 0x96
    /**请求帮派成员列表信息 */
    const UInt8 CLAN_PLAYER_LIST    = 0x67;// 0x97
    /**请求帮派科技信息 */
    const UInt8 CLAN_SKILL          = 0x69;// 0x99
    /**帮派驻地信息 */
    const UInt8 CLAN_BUILD          = 0x6A;// 0x9B
    /**帮会仓库 */
    const UInt8 CLAN_PACKAGE        = 0x6B;// 0x6B
    /**帮会仓库记录 */
    const UInt8 CLAN_PACKAGE_RECORD = 0x6C;
    /**帮派QQ群 */
    const UInt8 CLAN_QQ =             0x6D;
    /** 仙蕴晶石 **/
    const UInt8 FARIY_SPAR =          0x6E;
    /** 神魔之树 **/
    const UInt8 CLAN_SPIRIT_TREE    = 0x6F;
    /**请求宗族奖励物品 */
    const UInt8 CLANREWARD          = 0x9C;
    /**领取宗族奖励 */
    const UInt8 GET_CLANREWARD      = 0xFB;// 0x9D
    /**分配宗族奖励物品 */
    const UInt8 ALLOCATECLANREWARD  = 0x9E;
    /**宗族分配记录请求 */
    const UInt8 CLANALLOCRECORD     = 0x9F;
    /**帮派副本 */
    const UInt8 CLAN_COPY           = 0x5C;
    /**仙界遗址系统 */
    const UInt8 CLAN_FAIRYLAND      = 0x5D;
    /*结拜系统*/
    const UInt8 BROTHER             = 0x5E;
    /**邮件ID列表 */
    //const UInt8 MAIL_ID_LIST        = 0x40;// 0xA6
    ///**邮件信息列表 */
    //const UInt8 MAIL_LIST           = 0x41;// 0xA0
    ///**邮件内容 */
    //const UInt8 MAIL_CONTENT        = 0x42;// 0xA1
    ///**邮件删除 */
    //const UInt8 MAIL_DELETE         = 0x43;// 0xA2
    ///**邮件发送 */
    //const UInt8 MAIL_SEND           = 0x44;// 0xA3
    ///**邮件信息改变 */
    //const UInt8 MAIL_CHANGE         = 0x46;// 0xA5
    /** 全服乱斗 */
    const UInt8 RACE_BATTLE         = 0x4A;
    /**活跃度领取奖励 */
    const UInt8 ACTIVITY_REWARD     = 0x4B;
    /**活跃度签到积分 */
    const UInt8 ACTIVITY_SIGNIN     = 0x4C;
    /**变强之路*/
    const UInt8 STRENGTHEN_LIST     = 0x4D;
    /**仙界传奇*/
    const UInt8 SERVERWAR_ARENA_OP  = 0x4E;
    /**关系列表请求 */
    //const UInt8 FRIEND_LIST         = 0xD8;// 0xA8
    /**关系列表操作 */
    //const UInt8 FRIEND_ACTION       = 0xD9;// 0xA9
    /**商城信息请求 */
    const UInt8 STORE_LIST          = 0xDC;// 0xB0
    /**商城购买 */
    const UInt8 STORE_BUY           = 0xDD;// 0xB1
    /**根据交易ID请求交易内容 */
    const UInt8 TRADE_DATA          = 0x81;// 0xC1
    /**发起交易 */
    const UInt8 TRADE_LAUNCH        = 0x82;// 0xC2
    /**回复交易 */
    const UInt8 TRADE_REPLY         = 0x83;// 0xC3
    /**确认取消和删除交易状态操作 */
    const UInt8 TRADE_OPERATE       = 0x84;// 0xC4
    /**请求寄售列表 */
    const UInt8 SALE_LIST           = 0x85;// 0xC5
    /**发起寄售 */
    const UInt8 SALE_SELL           = 0x86;// 0xC6
    /**购买或下架指定物品 */
    const UInt8 SALE_OP             = 0x87;// 0xC7
    /**英雄岛 */
    const UInt8 HERO_ISLAND         = 0x97;
    const UInt8 NEWHERO_ISLAND      = 0xA6;
    /**设置密码 */
    const UInt8 OP_PWD              = 0xCD;
    /** */
    const UInt8 PWD_QUESTION        = 0xCB;
    /** */
    const UInt8 PWD_LOCK            = 0xCC;// 0xCE
    /**斗剑场信息 */
    const UInt8 ARENA_INFO          = 0xC5;// 0xD0
    /**斗剑场挑战 */
    //const UInt8 ARENA_FIGHT_INFO    = 0xC6;// 0xD1
    /**??? */
    const UInt8 ATHLETICS_CHALLENGE = 0xC6;//0xF8;// 0xD2
    /**刷新历练 */
    const UInt8 ATHLETICS_REFRESH_MARTIAL = 0xC7;
    /**斗剑领取奖励 */
    const UInt8 ATHLETICS_GET_AWARD = 0xC8;

    /**斗剑翻页 */
    const UInt8 ATHLETICS_PAGING    = 0xC9;
    /**斗剑去CD */
    const UInt8 ATHLETICS_KILLCD    = 0xCA;
    /**??? */
    const UInt8 ATTACK_BLOCKBOSS    = 0xD6;
    /**修炼地信息 */
    const UInt8 PLACE_INFO          = 0x30;// 0xE0
    /**修炼地翻页 */
    const UInt8 PRACTICE_PAGE_CHANGE= 0x31;// 0xE1
    /**修炼地挑战 */
    const UInt8 PLACE_ROB           = 0x32;// 0xE2
    /**修炼地占领 */
    const UInt8 PLACE_OCCUPY        = 0x33;// 0xE3
    /**开始修炼 */
    const UInt8 PRACTICE_START      = 0x34;// 0xE4
    /**停止修炼 */
    const UInt8 PRACTICE_STOP       = 0x35;// 0xE5
    /**修炼加速 */
    const UInt8 PRACTICE_HOOK_ADD   = 0x36;
    /**世界BOSS优化*/
    const UInt8 WBOSSOPT            = 0x3A;
    /**排行榜 */
    const UInt8 SORT_LIST           = 0xDA;// 0xE8
    /**玩家个人排行信息 */
    const UInt8 SORT_PERSON         = 0xDB;// 0xE9
    /**跨服战信息请求 */
    const UInt8 SERVER_ARENA_INFO   = 0xEA;
    /**请求对阵表 */
    const UInt8 SERVER_ARENA_LB     = 0xEB;
    /**跨服战-场外活动 */
    const UInt8 SERVER_ARENA_EXTRA_ACT = 0xE7;
    /**跨服战操作 */
    const UInt8 SERVER_ARENA_OP     = 0xE8;
    /**聊天 */

    /**私聊 */
    const UInt8 WHISPER             = 0x21;// 0xF1
    /**寻找玩家 */
    const UInt8 CHECK_USER          = 0x22;// 0xF2
    /**炫耀 */
    const UInt8 FLAUNT              = 0x23;// 0xF3
    /**BUG投诉 */
    const UInt8 BUG                 = 0x25;// 0xF8
    /***领取国庆礼包 */
    const UInt8 EXTEND_PROTOCAOL         = 0x27;

    const UInt8 YD_GETPACKS         = 0x2D;
    /**黄钻信息 */
    const UInt8 YD_INFO             = 0x2E;
    /**黄钻奖励领取 */
    const UInt8 YD_AWARD_RCV        = 0x2F;

    /**非战斗时信息请求 */
    const UInt8 CLAN_RANKBATTLE_REQINIT = 0x59;
    /**战斗时信息请求 */
    const UInt8 CLAN_RANKBATTLE_REQ     = 0x5A;
    /**帮会战排名列表 */
    const UInt8 CLAN_RANKBATTLE_SORTLIST = 0x5B;

    /** 法宝精炼 */
    const UInt8 EQ_TRUMP_UPGRADE    = 0xB7;
    /** 法宝升阶 */
    const UInt8 EQ_TRUMP_L_ORDER    = 0xB8;

    /***装备升级 */
    const UInt8 EQ_UPGRADE          = 0xB9;
    const UInt8 EQ_SPIRIT           = 0xBA;

    /**装备洗练属性解封 */
    const UInt8 EQ_ACTIVATE         = 0xBB;
    /**装备属性转移 */
    const UInt8 EQ_MOVE             = 0xBC;
    /**灵宝通灵*/
    const UInt8 EQ_LINGBAO          = 0xBD;
    /**多彩宝石*/
    const UInt8 EQ_DELUEGEM         = 0xBE;
    // const UInt8 GETBOX              = 0xD4;
    // const UInt8 BLOCKBOSS           = 0xD5;

    const UInt8 EQ_XINMO         = 0xBF;
    /** 组队副本 */
    const UInt8 TEAM_COPY_REQ       = 0x99;

    /** 宠物组队副本 */
    const UInt8 PET_TEAM_COPY       = 0x76;

    /** 墨宝 */
    const UInt8 MO_BAO              = 0x78;

    /** 夺宝奇兵 */
    const UInt8 DUOBAO_REQ          = 0x7E;

    /** 抗击天魔 */
    const UInt8 KANGJITIANMO_REQ    = 0x7F;

    /** 战报数据 */
    const UInt8 FIGHT_REPORT2       = 0x0F;

    /** 玩家战力对比*/
    const UInt8 COMPARE_BP          = 0xA7;

    /** 仙宠系统 */
    const UInt8 FAIRY_PET           = 0xA8;

    /** 锁妖塔 */
    const UInt8 TOWN_DEAMON         = 0xA9;

    /** 元神系统 */
    const UInt8 SECOND_SOUL         = 0x8E;
    /** 新手引导的UDPLOG请求 */
    const UInt8 GUIDEUDP            = 0xF4;
    /*回流服务器*/
    const UInt8 RP_SERVER           = 0xFE;

    const UInt8 FOURCOP             = 0x1F;
    /** 新关系 * */
    const UInt8 NEWRELATION         = 0x17;
    /** 符文 (内丹) * */
    const UInt8 SKILLSTRENGTHEN     = 0x18;
    /** 天劫 **/
    const UInt8 TIANJIE             = 0x19;
    /** 活动 **/
    const UInt8 ACTIVE              = 0x8B;

    /** 单挑 **/
    const UInt8 SINGLE_HERO         = 0XA5;
    /** 末日之战 **/
    const UInt8 CLANBOSS            = 0xF8;

    /** 墨守成规 */
    const UInt8 CCB                 = 0X26;
    /** 结婚系统 */
    const UInt8 MARRYMGR            = 0x75;
    /** 结婚养成 */
    const UInt8 MARRIEDMGR          = 0x77;
    /** 璇玑阵图*/
    const UInt8 XJFRONTMAP          = 0xE6;
    /** 卡牌系统*/
    const UInt8 COLLECTCARD         = 0x5F;
}

namespace REP
{
    const UInt8 CHAT                = 0x06;
    //强化
    const UInt8 SIGN                 =0x10;
    const UInt8 SIGN_INFO                 =0x11;

    const UInt8 ENCHART             = 0x20;// 0xF0
    const UInt8 ENCHARTSOLDIER      = 0x21;// 0xF0

    /*背包信息*/
    const UInt8 PACKAGE_INFO        = 0x30;// 0xE0
    /*抽将*/
    const UInt8 FIND_FIGHTER        = 0x31;// 
    const UInt8 FIND_INFO           = 0x32;// 
    const UInt8 UP_FIGHTER          =0x33;

    const UInt8 BATTLE_ARENA   = 0x83;// 0xC0

    /*好友列表*/
    const UInt8 FRIEND_LIST         = 0x40;
    /*好友查找*/
    const UInt8 FRIEND_FIND         = 0x41; //
    /*好友申请*/
    const UInt8 FRIEND_APPLY        = 0x42;
    /*好友添加*/
    const UInt8 FRIEND_ADD          = 0x43;
    /*好友删除*/
    const UInt8 FRIEND_DELETE       = 0x44;
    /*好友推荐*/
    const UInt8 FRIEND_RECOMMAND    = 0x45;
    /*好友基础信息*/
    const UInt8 FRIEND_BASEINFO     = 0x46;

 
    const UInt8 MAIL                = 0x50;// 

    const UInt8 MAIL_GET            = 0x51;// 

    const UInt8 MAIL_DELETE         = 0x52;// 

    const UInt8 MAIL_NOTICE         = 0x52;//

    const UInt8 MAIL_GET_ALL        = 0x53;//

    const UInt8 MAIL_DELETE_ALL     = 0x54;// 

    /*治理换将*/
    const UInt8 GOVERN_REPLACE      = 0x60;
    /*离线治理获得*/
    const UInt8 GOVERN_OFFLINE_GAIN = 0x61;
    /*治理加速*/
    const UInt8 GOVERN_SPEEDUP      = 0x62;
    /*请求治理信息*/
    const UInt8 GOVERN_INFO         = 0x63;
    /*在线治理获得*/
    const UInt8 GOVERN_ONLINE_GAIN  = 0x64;

    const UInt8 CLAN_LIST           = 0x70;
    
    const UInt8 CLAN_CREATE         = 0x71;

    //const UInt8 CLAN_FLASH        = 0x72;
    //
    const UInt8 CLAN_OPTION         = 0x73;

    const UInt8 CLAN_INFO           = 0x72;
    /*推图战役奖励*/
    const UInt8 BATTLE_AWARD        = 0x82;


    /*军团战报名*/
    const UInt8 CLAN_BATTLE_JOIN          = 0xA0;
    /*军团战加战将*/
    const UInt8 CLAN_BATTLE_ADDFIGHTER    = 0xA1;
    /*军团战移动战将*/
    const UInt8 CLAN_BATTLE_MOVEFIGHTER   = 0xA2;
    /*取消放置战将*/
    const UInt8 CLAN_BATTLE_CANCELFIGHTER = 0xA3;
    /*军团令*/
    const UInt8 CLAN_BATTLE_ORDERS        = 0xA4;
    /*留言*/
    const UInt8 CLAN_BATTLE_COMMENTS      = 0xA5;
    /*请求战报*/
    const UInt8 CLAN_BATTLE_REPORT        = 0xA6;
    /*战场信息*/
    const UInt8 CLAN_BATTLE_INFO          = 0xA7;

    const UInt8 CLAN_BATTLE_REPORTList    = 0xA8;

    const UInt8 CLAN_APPLY                = 0x74;


    /*开采换将*/
    const UInt8 EXPLOIT_REPLACE_FIGHTER   = 0xB0;
    /*资源采集返回*/
    const UInt8 EXPLOIT_COLLECT           = 0xB1;
    /*开采加速*/
    const UInt8 EXPLOIT_SPEEDUP           = 0xB2;

    /*商城物品信息请求*/
    const UInt8 STOREA_INFO               = 0xC0;
    /*商城购买刷新*/
    const UInt8 STOREA_FRESH              = 0xC1;
    /*商城物品购买*/
    const UInt8 STOREA_BUY                = 0xC2;


    const UInt8 KEEP_ALIVE          = 0x00;// 0x00
    const UInt8 RECONNECT           = 0x01;// 帐号被封
    const UInt8 ENTER_ARENA         = 0x02;
    const UInt8 LINEUP_CHANGE       = 0x03;
    const UInt8 NEXT_ARENA          = 0x04;
    const UInt8 CHKMARK             = 0x05;
    const UInt8 HEROMEMO            = 0x06;
    const UInt8 CFRIEND             = 0x07;
    const UInt8 OFFLINEEXP          = 0x08;
    const UInt8 TOKEN               = 0x09;
    const UInt8 ACHIEVEMENT         = 0xF0;// 0x0C
    const UInt8 CAMP_SELECT         = 0xF1;// 0x0D
    const UInt8 BE_DISCONNECT       = 0xF2;// 0x0E
    const UInt8 ALERT_MSG           = 0xF3;// 0x0F

    const UInt8 LOGIN               = 0xE0;// 0x10  //DOEN
    const UInt8 NEW_CHARACTER       = 0xE1;// 0x11  //DOEN
    const UInt8 USER_INFO_CHANGE    = 0xE3;
    const UInt8 CREATE_ACCOUNT      = 0xE5;// 0x15 //DOEN
    const UInt8 IDENTIFY_ACCOUNT    = 0xE6;// 0x15 //DOEN
    const UInt8 GMHAND              = 0xEF;
    

    const UInt8 WALLOW_VERIFY       = 0xE2;// 0x12
    //const UInt8 GUIDE_RESPONSE_STEP = 0xE3;// 0x13
    const UInt8 USER_INFO           = 0xE4;// 0x14

    const UInt8 STATE_CHANGE        = 0x16;
    const UInt8 RF7DAY              = 0x15;
    const UInt8 BOOK_SHOP_LIST      = 0xEC;// 0x1A
    const UInt8 ARENAPRILIMINARY    = 0xE9;// 0xED
    const UInt8 BOOK_SHOP_BUY       = 0xED;// 0x1B
    const UInt8 RANK_DATA           = 0xEE;// 0x1D
    const UInt8 RANK_SETTING        = 0xEF;// 0x1E

    const UInt8 CHANGE_EQUIPMENT    = 0xD0;// 0x21
    const UInt8 HOTEL_PUB_HIRE      = 0xD1;// 0x22
    const UInt8 FIGHTER_INFO        = 0xD2;// 0x23
    const UInt8 HOTEL_PUB_LIST      = 0xD3;// 0x26
    const UInt8 FIGHTER_DISMISS     = 0xD4;// 0x27
    const UInt8 FIGHTER_ACCEPT      = 0xD5;// 0x28
    const UInt8 PACK_USE_OTHER      = 0xD7;//
    const UInt8 PUB_LIST            = 0x2A;
    const UInt8 POTENCIAL           = 0xDF;// 0x2C

    const UInt8 TRAIN_FIGHTER_OP    = 0x37;

    const UInt8 PACK_INFO           = 0xC0;// 0x30
    const UInt8 MOFANG_INFO         = 0xFB;
    const UInt8 TEMPITEM_INFO       = 0xFA;
    const UInt8 PACK_USE            = 0xC3;// 0x33
    const UInt8 PACK_EXTEND         = 0xC4;// 0x34
    /**刷新历练 */
    const UInt8 ATHLETICS_REFRESH_MARTIAL = 0xC7;
    const UInt8 REWARD_DRAW         = 0xCF;// 0x38
    const UInt8 TRIPOD_INFO         = 0xCE;// 0x39
    const UInt8 LUCKYDRAW_INFO      = 0x3D;
    const UInt8 LUCKYDRAW           = 0x3E;
    const UInt8 LUCKYDRAW_OTH       = 0x3F;

    const UInt8 EQ_TO_STRONG        = 0xB0;// 0x40
    const UInt8 EQ_TO_PUNCH         = 0xB1;// 0x41
    const UInt8 EQ_EMBED            = 0xB2;// 0x43
    const UInt8 EQ_UN_EMBED         = 0xB3;// 0x44
    const UInt8 EQ_UN_SINGLE        = 0x45;
    const UInt8 EQ_EXCHANGE         = 0x46;
    const UInt8 EQ_PURIFY           = 0xB4;// 0x47
    const UInt8 EQ_BATCH_DECOMPOSE  = 0xB5;// 0x49
    const UInt8 EQ_EXCHANGE_POS     = 0x4A;
    const UInt8 GEM_BATCH_UPGRADE   = 0xB6;// 0x4B
    const UInt8 EQ_ACTIVE           = 0x4C;
    const UInt8 EQ_TRUMP_UPGRADE    = 0xB7;
    const UInt8 EQ_TRUMP_L_ORDER    = 0xB8;
    const UInt8 EQ_UPGRADE          = 0xB9;
    const UInt8 EQ_SPIRIT           = 0xBA;
    const UInt8 EQ_ACTIVATE         = 0xBB;
    const UInt8 EQ_MOVE             = 0xBC;
    const UInt8 EQ_LINGBAO          = 0xBD;
    const UInt8 EQ_DELUEGEM         = 0xBE;
    const UInt8 EQ_XINMO            = 0xBF;

    const UInt8 CITY_INSIDE_MOVE    = 0xA0;// 0x51
    const UInt8 MAP_TRANSPORT       = 0xA1;// 0x52
    const UInt8 MAP_TRANSPORT_UPDATE= 0xA2;// 0x53
    const UInt8 MAP_SAMPLEUSER      = 0xA3;// 0x54
    const UInt8 MAP_POINT_JOIN      = 0xA4;// 0x55
    const UInt8 MODIFY_MOUNT        = 0xAA;// 0x58
    const UInt8 COPY_DATA_UPDATE    = 0xAB;// 0x59
    const UInt8 COPY_FIGHT_RESULT   = 0xAC;// 0x5A
    const UInt8 COPY_AUTO_FIGHT     = 0xAD;// 0x5B
    const UInt8 COPY_END_FIGHT      = 0xAE;// 0x5C
    const UInt8 DAILY_DATA          = 0xAF;// 0x5F

    //const UInt8 CHANGE_NAME         = 0x60;
    const UInt8 COUNTRY_WAR_JOIN    = 0x90;// 0x62
    const UInt8 COUNTRY_WAR_PROCESS = 0x91;// 0x63
    const UInt8 COUNTRY_WAR_RESULT  = 0x92;// 0x64
    const UInt8 COUNTRY_WAR_STRING  = 0x93;// 0x66
    const UInt8 COPY_INFO           = 0x94;// 0x67
    const UInt8 FORMATTON_INFO      = 0x95;// 0x68
    const UInt8 AUTO_COPY           = 0x96;// ??
    const UInt8 AUTO_FRONTMAP       = 0x98;// ??
    const UInt8 FIGHT_START         = 0x9A;// 0x6C
    const UInt8 ATTACK_NPC          = 0x9B;// 0x61
    const UInt8 TASK_RESPONSE_HOOK  = 0x9D;// 0x6D

    //const UInt8 ERLKING_INFO        = 0x71;
    const UInt8 LANCHCHALLENGE      = 0x72;
    const UInt8 REQUESTCHALLENGE    = 0x73;
    const UInt8 MARRYBOARD          = 0x74;
    const UInt8 CLAN_TECH           = 0x78;
    const UInt8 CLAN_BATTLE         = 0x79;
    const UInt8 CLAN_OPEN           = 0x7A;
    const UInt8 CLAN_BATTLE_END     = 0x7B;
    //const UInt8 CLAN_INFO           = 0x7C;
    const UInt8 CLAN_DINFO_UPDATE   = 0x7D;

    const UInt8 DIALOG_START        = 0x50;// 0x80
    const UInt8 DIALOG_INTERACTION  = 0x51;// 0x81
    const UInt8 GET_TASK_LIST       = 0x52;// 0x82
    const UInt8 GET_USABLE_TASK     = 0x53;// 0x83
    const UInt8 PLAYER_ABANDON_TASK = 0x54;// 0x85
    const UInt8 UPDATE_TASK_PROCESS = 0x55;// 0x86
    const UInt8 NEW_TASK            = 0x56;// 0x87

    const UInt8 CONVEYBATTLE        = 0x88;
    const UInt8 COLLECTNPCACTION    = 0x89;
    const UInt8 TASK_CYC_STATE      = 0x8A;

    const UInt8 TASK_CYC_FRESH      = 0x57;// 0x8B

    const UInt8 ACT                 = 0x8B;
    const UInt8 AUTO_COMPLETED_TASK = 0x8D;
    const UInt8 QUERYDAYTASK        = 0x8F;

    const UInt8 CLAN_REQ_LIST       = 0x60;// 0x90
    //const UInt8 CLAN_REQ_USER       = 0x61;// 0x91
    //const UInt8 CLAN_CREATE         = 0x62;// 0x92
    //const UInt8 CLAN_REQ_USER       = 0x61;// 0x91
    //const UInt8 CLAN_CREATE         = 0x62;// 0x92
    const UInt8 CLAN_JOIN_IN        = 0x63;// 0x93
    const UInt8 CLAN_MEMBER_OPERATE = 0x64;// 0x94
    const UInt8 CLAN_INFO_CHANGE    = 0x65;// 0x95
    const UInt8 CLAN_REQ_ITEM       = 0x66;// 0x96
    const UInt8 CLAN_MEMBER_LIST    = 0x67;// 0x97
    const UInt8 CLAN_INFO_UPDATE    = 0x68;// 0x98
    const UInt8 CLAN_SKILL          = 0x69;// 0x99
    const UInt8 CLAN_BUILD          = 0x6A;// 0x9B
    const UInt8 CLAN_PACKAGE        = 0x6B;//
    const UInt8 CLAN_PACKAGE_RECORD = 0x6C;
    const UInt8 CLAN_QQ =             0x6D;
    /** 仙蕴晶石 **/
    const UInt8 FARIY_SPAR =          0x6E;
    /** 神魔之树 **/
    const UInt8 CLAN_SPIRIT_TREE    = 0x6F;

    const UInt8 HERO_ISLAND         = 0x97;
    const UInt8 NEWHERO_ISLAND      = 0xA6;
    const UInt8 CLANREWARD          = 0x9C;
    const UInt8 GET_CLANREWARD      = 0x9D;
    const UInt8 ALLOCATECLANREWARD  = 0x9E;
    const UInt8 CLANALLOCRECORD     = 0x9F;

    const UInt8 CLAN_COPY           = 0x5C;
    const UInt8 CLAN_FAIRYLAND      = 0x5D;
    const UInt8 BROTHER             = 0x5E;

    const UInt8 MAIL_ID_LIST        = 0x40;// 0xA6
    const UInt8 MAIL_LIST           = 0x41;// 0xA0
    const UInt8 MAIL_CONTENTS       = 0x42;// 0xA1
    //const UInt8 MAIL_DELETE         = 0x43;// 0xA2
    const UInt8 MAIL_SEND           = 0x44;// 0xA3
    const UInt8 MAIL_NEW            = 0x45;// 0xA4
    const UInt8 MAIL_CHANGE         = 0x46;// 0xA5

    /** 全服乱斗 */
    const UInt8 RACE_BATTLE         = 0x4A;
    /** 活跃度领取奖励 */
    const UInt8 ACTIVITY_REWARD     = 0x4B;
    const UInt8 ACTIVITY_SIGNIN     = 0x4C;
    /**变强之路*/
    const UInt8 STRENGTHEN_LIST     = 0x4D;
    /**仙界传奇*/
    const UInt8 SERVERWAR_ARENA_OP  = 0x4E;

    //const UInt8 FRIEND_LIST         = 0xD8;// 0xA8
    const UInt8 FRIEND_ACTION       = 0xD9;// 0xA9

    const UInt8 STORE_LIST          = 0xDC;// 0xB0
    const UInt8 STORE_BUY           = 0xDD;// 0xB1
    const UInt8 STORE_LIST_EXCHANGE = 0xDE;// ??
    const UInt8 STORE_DISLIMIT      = 0x0A;
    const UInt8 RC7DAY              = 0x0B;
    const UInt8 SSAWARD             = 0x0C;
    const UInt8 USESOUL             = 0x0D;
    const UInt8 SVRST               = 0x11;
    const UInt8 YBBUF               = 0x12;
    const UInt8 GETAWARD            = 0x13;
    const UInt8 LUCKY_RANK          = 0x14;
    /** 各种活动 **/
    const UInt8 COUNTRY_ACT         = 0x1B;

    /** 新版出生七天活动 */
    const UInt8 NEWRC7DAY           = 0x1C;


    /** 墨家面板协议 */
    const UInt8 EXJOB               = 0x1D;
    /** 墨家游戏协议 */
    const UInt8 JOBHUNTER           = 0x1E;
    /** 自动寻墨游戏 */
    const UInt8 AUTOJOBHUNTER       = 0X2A;
    /** 水晶梦境协议 */
    const UInt8 DREAMER             = 0x29;

    const UInt8 TRADE_LIST          = 0x80;// 0xC0
    const UInt8 TRADE_DATA          = 0x81;// 0xC1
    const UInt8 TRADE_LAUNCH        = 0x82;// 0xC2
    const UInt8 TRADE_OPERATE       = 0x84;// 0xC4
    const UInt8 SALE_LIST           = 0x85;// 0xC5
    const UInt8 SALE_SELL           = 0x86;// 0xC6
    const UInt8 OP_PWD              = 0xCD;
    const UInt8 SECOND_PWD          = 0xCB;
    const UInt8 PWD_DAILOG          = 0xCA;
    const UInt8 PWD_LOCK            = 0xCC;

    const UInt8 ARENA_IFNO          = 0xC5;// 0xD0
    const UInt8 FIGHT_INFO_CHANGE   = 0xC6;// 0xD1

    const UInt8 PRACTICE_PLACE_IFNO = 0x30;// 0xE0
    const UInt8 PRACTICE_PAGE       = 0x31;// 0xE1
    const UInt8 PRACTICE_ROB        = 0x32;// 0xE2
    const UInt8 PRACTICE_OCCUPY     = 0x33;// 0xE3
    const UInt8 PRACTICE_START      = 0x34;// 0xE4
    const UInt8 PRACTICE_STOP       = 0x35;// 0xE5
    const UInt8 PRACTICE_HOOK_ADD   = 0x36;
    
    const UInt8 WBOSSOPT            = 0x3A;

    const UInt8 SORT_LIST           = 0xDA;// 0xE8
    const UInt8 SORT_PERSONAL       = 0xDB;// 0xE9
    const UInt8 SERVER_ARENA_INFO   = 0xEA;
    const UInt8 SERVER_ARENA_LB     = 0xEB;

    //const UInt8 CHAT                = 0x20;// 0xF0
    const UInt8 CHAT_PRIVATE        = 0x21;// 0xF1
    const UInt8 FIND_USER           = 0x22;// 0xF2
    const UInt8 FLAUNT_GOOD         = 0x23;// 0xF3
    const UInt8 SYSTEM_INFO         = 0x24;// 0xF7
    const UInt8 BUG_INFO            = 0x25;// 0xF8

    const UInt8 EXTEND_PROTOCAOL    = 0x27;//  扩展协议
    const UInt8 YD_GETPACKS         = 0x2D;
    const UInt8 YD_INFO             = 0x2E;
    const UInt8 YD_AWARD_RCV        = 0x2F;
    /**加入新国战 */
    const UInt8 NEW_CAMPS_WAR_JOIN  = 0x2B;

    /**跨服战-场外活动 */
    const UInt8 SERVER_ARENA_EXTRA_ACT = 0xE7;
    const UInt8 SERVER_ARENA_OP     = 0xE8;

    const UInt8 ATHLETICS_CHALLENGE = 0xF5;// 0xD2
    const UInt8 WINSTREAK           = 0xF6;// 0xD3
    const UInt8 GETBOX              = 0xF7;// 0xD4
    const UInt8 BLOCKBOSS           = 0xF9;// 0xD5

    const UInt8 CLANBOSS           = 0xF8;// 0xD5

    const UInt8 CLAN_RANKBATTLE_REPINIT = 0x59;  //非战斗时信息返回
    const UInt8 CLAN_RANKBATTLE_REP     = 0x5A;  //战斗时信息返回
    const UInt8 CLAN_RANKBATTLE_SORTLIST = 0x5B; //帮会战排名列表

    const UInt8 TEAM_COPY_REQ       = 0x99;

    const UInt8 PET_TEAM_COPY       = 0x76;

    /** 墨宝 */
    const UInt8 MO_BAO              = 0x78;

    /** 夺宝奇兵 */
    const UInt8 DUOBAO_REP          = 0x7E;

    /** 抗击天魔 */
    const UInt8 KANGJITIANMO_REP    = 0x7F;

    /** 战报数据 */
    const UInt8 FIGHT_REPORT2       = 0x0F;

    /** 系统弹窗公告 */
    const UInt8 SYSDAILOG           = 0x0E;

    /** 玩家战力对比*/
    const UInt8 COMPARE_BP          = 0xA7;

    /** 仙宠系统 */
    const UInt8 FAIRY_PET           = 0xA8;

    /** 锁妖塔 */
    const UInt8 TOWN_DEAMON         = 0xA9;

    /** 元神系统 */
    const UInt8 SECOND_SOUL         = 0x8E;
    /*回流服务器*/
    const UInt8 RP_SERVER           = 0xFE;

    const UInt8 FOURCOP             = 0x1F;
    /** 新关系 * */
    const UInt8 NEWRELATION         = 0x17;
    /** 符文 (内丹) * */
    const UInt8 SKILLSTRENGTHEN     = 0x18;
    /** 天劫 **/
    const UInt8 TIANJIE             = 0x19;
    /** 活动 **/
    const UInt8 ACTIVE              = 0x8B;

    /** 单挑 **/
    const UInt8 SINGLE_HERO         = 0XA5;
    /** 墨守成规 */
    const UInt8 CCB                 = 0X26;
    /** 结婚系统 */
    const UInt8 MARRYMGR            = 0x75;
    /** 结婚养成 */
    const UInt8 MARRIEDMGR          = 0x77;
    /** 璇玑阵图*/
    const UInt8 XJFRONTMAP          = 0xE6;
    /** 卡牌系统*/
    const UInt8 COLLECTCARD         = 0x5F;
}

namespace SPEQ
{
    const UInt8 SOCK_ADDR           = 0x02;
    const UInt8 PLAYERIDAUTH        = 0xFC;// 0xFD
    const UInt8 WORLDANNOUNCE       = 0xFD;// 0xFE
    const UInt16 USERRECHARGE       = 0x105;// 0x100
    const UInt16 KILLUSER           = 0x104;// 0x101
    const UInt16 LOCKUSER           = 0x100;// 0x102
    const UInt16 UNLOCKUSER         = 0x101;// 0x103
    const UInt16 GMHANDLERFROMBS    = 0x102;// 0x104
    const UInt16 MAILFROMBS         = 0x107;// 0x105
    const UInt16 BANCHATFROMBS      = 0x103;// 0x106
    const UInt16 ADDITEMFROMBS      = 0x108;// 0x107
    const UInt16 BATTLEREPORT       = 0x106;// 0x110
    const UInt16 RERECHARGE         = 0x109;//
    const UInt16 ONLINE             = 0x10A;//
    const UInt16 SETLEVEL           = 0x10B;//
    const UInt16 ADDITEMTOALL       = 0x10C;//
    const UInt16 SETPROPS           = 0x10D;//
    const UInt16 SETMONEY           = 0x10E;//
    const UInt16 LOADLUA            = 0x10F;//
    const UInt16 SETVIPL            = 0x110;//
    const UInt16 CLSTASK            = 0x111;//
    const UInt16 SALE_ONOFF         = 0x112;// 交易开关
    const UInt16 PLAYERINFO         = 0x113;
    const UInt16 WBOSS              = 0x114;
    const UInt16 ONLINEPF           = 0x115;
    const UInt16 ADDITEMFROMBSBYID  = 0x116;
    const UInt16 ADDFIGHTER         = 0x117;
    const UInt16 GETMONEY           = 0x118;
    const UInt16 SYSDAILOG          = 0x119;
    const UInt16 PWDINFO            = 0x11A;
    const UInt16 PWDRESET           = 0x11B;
    const UInt16 MAILVIP            = 0x11C;
    const UInt16 JASON              = 0x11D;//PHP过来的JASON请求
    const UInt16 CFRIEND            = 0x11E;//设置成密友
    const UInt16 ADDITEMFROMBSBYCOUNTRY = 0x11F;//根据阵营发奖励

    const UInt16 GMCMD               = 0x120; // 接受GM命令

    const UInt16 ADDDISCOUNT         = 0x121; // 增加限时活动
    const UInt16 QUERYDISCOUNT       = 0x122; // 查询限时活动
    const UInt16 CLEARDISCOUNT       = 0x123; // 清空限时活动
    const UInt16 REALAWARDINFO       = 0x124; //
    const UInt16 ADDREALAWARD        = 0x125; //

    const UInt16 ADDCLANAWARD        = 0x128; // 发放物品给帮派仓库
    const UInt16 MANUALOPENTJ        = 0x129; // 手动开启天劫
    const UInt16 SHSTAGEONOFF        = 0x130; // 职业第一开关
    const UInt16 QUERYSHSTAGEONOFF   = 0x131; // 查询职业第一
    const UInt16 BIGLOCKUSER         = 0x132;// 0x102
    const UInt16 BIGUNLOCKUSER       = 0x133;// 0x103
    const UInt16 CLSTASKALL          = 0x134;//
    const UInt16 FORBIDSALE          = 0x135;// 全区禁止交易
    const UInt16 UNFORBIDSALE        = 0x136;// 全区解除禁止交易
    const UInt16 QUERYLOCKUSER       = 0x137;// 查询玩家是否被禁止登陆和交易
    const UInt16 SETLOGINLIMIT       = 0x138;// 设置平台一个ip最大登录数
    const UInt16 DELETEGOLD          = 0x139;// 删除仙石
    const UInt16 ADDRECHARGESCORE    = 0x140;// 增加充值的积分
    const UInt16 SYSUPDATE           = 0x141;// 系统更新公告
    const UInt16 FB_SPECIFY_FIND     = 0x142;// FB-隆中网络查询
    const UInt16 ACTIVITYONOFF       = 0x143;// 后台操作活动开关
    const UInt16 QUERYACTIVITYONOFF  = 0x144;// 后台查询活动开启状态
    const UInt16 OPENCB              = 0x145;// 开启末日之战
    const UInt16 TOTALRECHARGEACT    = 0x146;// 活动期间的充值总额
    const UInt16 SETTOTALRECHARGEACT = 0x147;// 设置活动区间
    const UInt16 SETMAXNEWUSER       = 0x148;// modify max create role
    const UInt16 GETMAXNEWUSER       = 0x149;
    const UInt16 SETRECHARGERANK     = 0x14A;// FB设置充值排行
    const UInt16 OFFQQOPENID         = 0x14B;// 解除QQ群绑定 
    const UInt16 GETQQCLANTALK       = 0x14C;// 接收QQ群聊天记录
    const UInt16 SETVAR              = 0x14D;// 设置VAR
    const UInt16 VIAPLAYERINFO       = 0x14E;// 查询导入玩家信息
    const UInt16 SETMARRYBOARD          = 0x14F;// 设置婚礼 
    const UInt16 WORLDCUP          = 0x151;// 设置世界杯答案
}

namespace SPEP
{
    const UInt8 LOCKUSER            = 0x00;
    const UInt8 UNLOCKUSER          = 0x01;
    const UInt8 GMHANDLERFROMBS     = 0x02;
    const UInt8 USERRECHARGE        = 0x05;
    const UInt8 MAILFROMBS          = 0x07;
    const UInt8 BANCHATFROMBS       = 0x03;
    const UInt8 ADDITEMFROMBS       = 0x08;
    const UInt8 RERECHARGE          = 0x09;//
    const UInt8 ONLINE              = 0x0A;//
    const UInt8 SETLEVEL            = 0x0B;//
    const UInt8 ADDITEMTOALL        = 0x0C;//
    const UInt8 SETPROPS            = 0x0D;//
    const UInt8 SETMONEY            = 0x0E;//
    const UInt8 LOADLUA             = 0x0F;//
    const UInt8 SETVIPL             = 0x10;//
    const UInt8 CLSTASK             = 0x11;//
    const UInt8 PLAYERIDAUTH        = 0xFC;// 0xFD
    const UInt8 SALE_ONOFF          = 0x12;// 交易开关
    const UInt8 PLAYERINFO          = 0x13;
    const UInt8 WBOSS               = 0x14;
    const UInt8 ONLINEPF            = 0x15;
    const UInt8 ADDITEMFROMBSBYID   = 0x16;
    const UInt8 ADDFIGHTER          = 0x17;
    const UInt8 GETMONEY            = 0x18;
    const UInt8 PWDINFO             = 0x1A;
    const UInt8 PWDRESET            = 0x1B;
    const UInt8 MAILVIP             = 0x1C;
    const UInt8 JASON               = 0x1D;
    const UInt8 CFRIEND             = 0x1E;//设置成密友
    const UInt8 ADDITEMFROMBSBYCOUNTRY = 0x1F;//阵营发奖励
    const UInt8 GMCMD               = 0x20; // 接受GM命令
    const UInt8 ADDDISCOUNT         = 0x21; // 增加限时活动
    const UInt8 QUERYDISCOUNT       = 0x22; // 查询限时活动
    const UInt8 CLEARDISCOUNT       = 0x23; // 清空限时活动

    const UInt8 REALAWARDINFO       = 0x24; //
    const UInt8 ADDREALAWARD        = 0x25; //
    const UInt8 ADDCLANAWARD        = 0x28; // 发放物品给帮派仓库
    const UInt8 MANUALOPENTJ        = 0x29; //手动开启天劫 
    const UInt8 SHSTAGEONOFF        = 0x30; // 职业第一开关
    const UInt8 QUERYSHSTAGEONOFF   = 0x31; // 查询职业第一
    const UInt8 BIGLOCKUSER         = 0x32;
    const UInt8 BIGUNLOCKUSER       = 0x33;
    const UInt8 CLSTASKALL          = 0x34;//
    const UInt8 FORBIDSALE          = 0x35;// 全区禁止交易
    const UInt8 UNFORBIDSALE        = 0x36;// 全区解除禁止交易
    const UInt8 QUERYLOCKUSER       = 0x37;// 查询玩家是否被禁止登陆和交易
    const UInt8 SETLOGINLIMIT       = 0x38;// 设置平台一个ip最大登录数
    const UInt8 DELETEGOLD          = 0x39;// 删除仙石
    const UInt8 ADDRECHARGESCORE    = 0x40;// 增加充值的积分
    const UInt8 SYSUPDATE           = 0x41;// 系统更新公告
    const UInt8 FB_SPECIFY_FIND     = 0x42;// FB-隆中网络查询
    const UInt8 ACTIVITYONOFF       = 0x43;// 后台操作活动开关
    const UInt8 QUERYACTIVITYONOFF  = 0x44;// 后台查询活动开启状态
    const UInt8 OPENCB              = 0x45;// 开启末日之战
    const UInt8 TOTALRECHARGEACT    = 0x46;// 活动期间的充值总额
    const UInt8 SETTOTALRECHARGEACT = 0x47;// 设置活动区间
    const UInt8 SETMAXNEWUSER       = 0x48;// modify max create role
    const UInt8 GETMAXNEWUSER       = 0x49;// get max create role
    const UInt8 SETRECHARGERANK     = 0x4A;// FB设置充值排行
    const UInt8 OFFQQOPENID         = 0x4B;// 解除QQ群绑定 
    const UInt8 GETQQCLANTALK       = 0x4C;// 接收QQ群聊天记录
    const UInt8 SETVAR              = 0x4D;//设置var
    const UInt8 VIAPLAYERINFO       = 0x4E;// 查询导入玩家信息
    const UInt8 SETMARRYBOARD       = 0x4F;//设置婚礼
    const UInt8 WORLDCUP            = 0x51;//设置世界杯押注结果

}

namespace ARENAREQ
{
    const UInt8 REG                 = 0x01;
    const UInt8 ENTER               = 0x02;
    const UInt8 COMMIT_LINEUP       = 0x03;
    const UInt8 RECHARGE_ACTIVE     = 0x06;
    const UInt8 BET                 = 0x07;
    const UInt8 BATTLE_REPORT       = 0x08;
    const UInt8 TEAMARENA_ENTER     = 0x10;
    const UInt8 TEAMARENA_LINEUP    = 0x11;
    const UInt8 TEAMARENA_INSPIRE   = 0x12;
}

namespace SERVERWARREQ
{
    const UInt8 REG                 = 0x01;
    const UInt8 ENTER               = 0x02;
    const UInt8 COMMIT_LINEUP       = 0x03;
    const UInt8 BET                 = 0x04;
    const UInt8 BATTLE_REPORT       = 0x05;
    const UInt8 RECHARGE_ACTIVE     = 0x06;
    const UInt8 SAY_TO_WORLD     = 0x07;
    
    const UInt8 ARENA_TO_SERVERWAR  = 0x10;     //"仙界第一/仙界至尊"TCP连接"仙界传奇" 占用
}

enum CLAN_COPY
{
    CLAN_COPY_TAB_INFO = 0x01,
    CLAN_COPY_BROAD_CAST = 0x02,
    CLAN_COPY_MEMBER_LIST_OP = 0x03,
    CLAN_COPY_BATTLE = 0x04,
};

namespace SERVERLEFTREQ
{
    const UInt8 REG                 = 0x01;
    const UInt8 ENTER               = 0x02;
    const UInt8 COMMIT_LINEUP       = 0x03;
    const UInt8 BET                 = 0x04;
    const UInt8 BATTLE_REPORT       = 0x05;
    const UInt8 LEFTADDR_INFO       = 0x06;
    const UInt8 LEFTADDR_SWITCHPLAYER       = 0x07;
    const UInt8 LEFTADDR_POWERHOLD       = 0x08;
    
    const UInt8 ARENA_TO_SERVERWAR  = 0x10;     //"仙界第一/仙界至尊"TCP连接"仙界传奇" 占用
}
#endif // __ASSS_MSGID_H_

