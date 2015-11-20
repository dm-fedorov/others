
use pcap2mysql_data;

/*select ip.hlen,ip.flags,ip.ttl,ip.proto,udp.d_port,udp.len from ip, udp where ip.id=udp.id;*/
/*select ip.hlen,ip.flags,ip.ttl,ip.proto,tcp.d_port,tcp.seqnum,tcp.acknum,tcp.hlen,tcp.flags,tcp.winsize,tcp.urg from ip, tcp where ip.id=tcp.id;*/

/*insert into pcap_weka (id,ip_hlen,ip_flags,ip_ttl,ip_proto,udp_d_port,udp_len) select ip.id, ip.hlen,ip.flags,ip.ttl,ip.proto,udp.d_port,udp.len from ip, udp where ip.id=udp.id;*/

drop database pcap2mysql_data;
drop database pcap2mysql_data;
drop database pcap2mysql_data;
drop database pcap2mysql_data;

insert into pcap_weka (id,ip_s,ip_d,ip_hlen,ip_flags,ip_ttl,ip_proto,tcp_s_port,tcp_d_port,tcp_seqnum,tcp_acknum,tcp_hlen,tcp_flags,tcp_winsize,tcp_urg, tcp_data_len) select ip.id,ip.s_ip,ip.d_ip,ip.hlen,ip.flags,ip.ttl,ip.proto,tcp.s_port,tcp.d_port,tcp.seqnum,tcp.acknum,tcp.hlen,tcp.flags,tcp.winsize,tcp.urg,ip.len-ip.hlen*4-tcp.hlen*4  from ip, tcp where ip.id=tcp.id; 

//////////////////////////////////////

/* 0) создали таблицу */

CREATE TABLE `time_packet` (
  `pos` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `id` bigint(20) unsigned NOT NULL default '0',
  `datetime` int(11) unsigned default NULL,
  `usec` int(10) unsigned NOT NULL default '0',
  `packet_time` int(11) unsigned default NULL,
  PRIMARY KEY  (`pos`),
  KEY `datetime` (`datetime`)
) TYPE=MyISAM;

/* заполнение данными */

/* заполнение временем */

/* 1) создали таблицу */

CREATE TABLE `pcap_weka` (
  `id` bigint(20) unsigned NOT NULL default '0',  
  `packet_time` int(11) unsigned default NULL,
  `ip_s` char(15) NOT NULL default '',
  `ip_d` char(15) NOT NULL default '',  
  `ip_flags` tinyint(1) unsigned NOT NULL default '0',
  `ip_ttl` tinyint(1) unsigned NOT NULL default '0',  
  `tcp_s_port` int(3) unsigned NOT NULL default '0',
  `tcp_d_port` int(3) unsigned NOT NULL default '0',  
  `tcp_flags` tinyint(3) unsigned NOT NULL default '0',
  `tcp_winsize` smallint(5) unsigned NOT NULL default '0',  
  `tcp_data_len` smallint(5) unsigned NOT NULL default '0',
  `tcp_flow_dir` smallint(5) unsigned NOT NULL default '0',
  `app_proto` smallint(5) unsigned NOT NULL default '0',
  `app_proto_name` varchar(10) NOT NULL default '',
  PRIMARY KEY  (`id`)
) TYPE=MyISAM;

/* 1 */
insert into pcap_weka (id,packet_time,ip_s,ip_d,ip_flags,ip_ttl,tcp_s_port,tcp_d_port,tcp_flags,tcp_winsize,tcp_data_len) select ip.id,time_packet.packet_time,ip.s_ip,ip.d_ip,ip.flags,ip.ttl,tcp.s_port,tcp.d_port,tcp.flags,tcp.winsize,ip.len-ip.hlen*4-tcp.hlen*4  from ip, tcp,time_packet where ip.id=tcp.id and time_packet.id=tcp.id; 

/* заполнили протокол */

/* 0) Создание таблицы */

/* tcp + время */

CREATE TABLE `pcap_weka` (
  `pos` bigint(20) unsigned NOT NULL AUTO_INCREMENT,  
  `id` bigint(20) unsigned NOT NULL default '0',  
  `packet_time` int(11) unsigned default NULL,
  `datetime` int(11) unsigned default NULL,
  `usec` int(10) unsigned NOT NULL default '0',
  `ip_s` char(15) NOT NULL default '',
  `ip_d` char(15) NOT NULL default '',  
  `ip_flags` tinyint(1) unsigned NOT NULL default '0',
  `ip_ttl` tinyint(1) unsigned NOT NULL default '0',  
  `tcp_s_port` int(3) unsigned NOT NULL default '0',
  `tcp_d_port` int(3) unsigned NOT NULL default '0',  
  `tcp_winsize` smallint(5) unsigned NOT NULL default '0',  
  `tcp_data_len` smallint(5) unsigned NOT NULL default '0',
  `tcp_flow_dir` smallint(5) unsigned NOT NULL default '0',
  `app_proto` smallint(5) unsigned NOT NULL default '0',
  `app_proto_name` varchar(10) NOT NULL default '',
  PRIMARY KEY  (`pos`)
) TYPE=MyISAM;

/* 1) Подготовка */
insert into pcap_weka (id,ip_s,ip_d,ip_flags,ip_ttl,tcp_s_port,tcp_d_port,tcp_winsize,tcp_data_len) select ip.id,ip.s_ip,ip.d_ip,ip.flags,ip.ttl,tcp.s_port,tcp.d_port,tcp.winsize,ip.len-ip.hlen*4-tcp.hlen*4  from ip, tcp where ip.id=tcp.id; 

insert into pcap_weka (id,ip_s,ip_d,ip_flags,ip_ttl,tcp_s_port,tcp_d_port,tcp_winsize,tcp_data_len) select ip.id,ip.s_ip,ip.d_ip,ip.flags,ip.ttl,tcp.s_port,tcp.d_port,tcp.winsize,ip.len-ip.hlen*4-tcp.hlen*4  from ip, tcp where ip.id=tcp.id; 

/* 2)  */
update pcap_weka,pcap set pcap_weka.datetime=pcap.datetime, pcap_weka.usec=pcap.usec where pcap_weka.id=pcap.id;

delete from pcap_weka where app_proto=0;

insert into pcap_weka (id,ip_s,ip_d,ip_flags,ip_ttl,tcp_s_port,tcp_d_port,tcp_flags,tcp_winsize,tcp_data_len) select ip.id,ip.s_ip,ip.d_ip,ip.flags,ip.ttl,tcp.s_port,tcp.d_port,tcp.flags,tcp.winsize,ip.len-ip.hlen*4-tcp.hlen*4  from ip, tcp where ip.id=tcp.id; 