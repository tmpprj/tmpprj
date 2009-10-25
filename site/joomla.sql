-- MySQL dump 10.13  Distrib 5.1.37, for debian-linux-gnu (x86_64)
--
-- Host: localhost    Database: joom
-- ------------------------------------------------------
-- Server version	5.1.37-1ubuntu5

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `jos_banner`
--

DROP TABLE IF EXISTS `jos_banner`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `jos_banner` (
  `bid` int(11) NOT NULL AUTO_INCREMENT,
  `cid` int(11) NOT NULL DEFAULT '0',
  `type` varchar(30) NOT NULL DEFAULT 'banner',
  `name` varchar(255) NOT NULL DEFAULT '',
  `alias` varchar(255) NOT NULL DEFAULT '',
  `imptotal` int(11) NOT NULL DEFAULT '0',
  `impmade` int(11) NOT NULL DEFAULT '0',
  `clicks` int(11) NOT NULL DEFAULT '0',
  `imageurl` varchar(100) NOT NULL DEFAULT '',
  `clickurl` varchar(200) NOT NULL DEFAULT '',
  `date` datetime DEFAULT NULL,
  `showBanner` tinyint(1) NOT NULL DEFAULT '0',
  `checked_out` tinyint(1) NOT NULL DEFAULT '0',
  `checked_out_time` datetime NOT NULL DEFAULT '0000-00-00 00:00:00',
  `editor` varchar(50) DEFAULT NULL,
  `custombannercode` text,
  `catid` int(10) unsigned NOT NULL DEFAULT '0',
  `description` text NOT NULL,
  `sticky` tinyint(1) unsigned NOT NULL DEFAULT '0',
  `ordering` int(11) NOT NULL DEFAULT '0',
  `publish_up` datetime NOT NULL DEFAULT '0000-00-00 00:00:00',
  `publish_down` datetime NOT NULL DEFAULT '0000-00-00 00:00:00',
  `tags` text NOT NULL,
  `params` text NOT NULL,
  PRIMARY KEY (`bid`),
  KEY `viewbanner` (`showBanner`),
  KEY `idx_banner_catid` (`catid`)
) ENGINE=MyISAM AUTO_INCREMENT=9 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `jos_banner`
--

LOCK TABLES `jos_banner` WRITE;
/*!40000 ALTER TABLE `jos_banner` DISABLE KEYS */;
INSERT INTO `jos_banner` VALUES (1,1,'banner','OSM 1','osm-1',0,43,0,'osmbanner1.png','http://www.opensourcematters.org','2004-07-07 15:31:29',0,0,'0000-00-00 00:00:00','','',13,'',0,1,'0000-00-00 00:00:00','0000-00-00 00:00:00','',''),(2,1,'banner','OSM 2','osm-2',0,49,0,'osmbanner2.png','http://www.opensourcematters.org','2004-07-07 15:31:29',0,0,'0000-00-00 00:00:00','','',13,'',0,2,'0000-00-00 00:00:00','0000-00-00 00:00:00','',''),(3,1,'','Joomla!','joomla',0,30,0,'','http://www.joomla.org','2006-05-29 14:21:28',0,0,'0000-00-00 00:00:00','','<a href=\"{CLICKURL}\" target=\"_blank\">{NAME}</a>\r\n<br/>\r\nJoomla! The most popular and widely used Open Source CMS Project in the world.',14,'',0,1,'0000-00-00 00:00:00','0000-00-00 00:00:00','',''),(4,1,'','JoomlaCode','joomlacode',0,30,0,'','http://joomlacode.org','2006-05-29 14:19:26',0,0,'0000-00-00 00:00:00','','<a href=\"{CLICKURL}\" target=\"_blank\">{NAME}</a>\r\n<br/>\r\nJoomlaCode, development and distribution made easy.',14,'',0,2,'0000-00-00 00:00:00','0000-00-00 00:00:00','',''),(5,1,'','Joomla! Extensions','joomla-extensions',0,25,0,'','http://extensions.joomla.org','2006-05-29 14:23:21',0,0,'0000-00-00 00:00:00','','<a href=\"{CLICKURL}\" target=\"_blank\">{NAME}</a>\r\n<br/>\r\nJoomla! Components, Modules, Plugins and Languages by the bucket load.',14,'',0,3,'0000-00-00 00:00:00','0000-00-00 00:00:00','',''),(6,1,'','Joomla! Shop','joomla-shop',0,25,0,'','http://shop.joomla.org','2006-05-29 14:23:21',0,0,'0000-00-00 00:00:00','','<a href=\"{CLICKURL}\" target=\"_blank\">{NAME}</a>\r\n<br/>\r\nFor all your Joomla! merchandise.',14,'',0,4,'0000-00-00 00:00:00','0000-00-00 00:00:00','',''),(7,1,'','Joomla! Promo Shop','joomla-promo-shop',0,13,1,'shop-ad.jpg','http://shop.joomla.org','2007-09-19 17:26:24',0,0,'0000-00-00 00:00:00','','',33,'',0,3,'0000-00-00 00:00:00','0000-00-00 00:00:00','',''),(8,1,'','Joomla! Promo Books','joomla-promo-books',0,20,0,'shop-ad-books.jpg','http://shop.joomla.org/amazoncom-bookstores.html','2007-09-19 17:28:01',0,0,'0000-00-00 00:00:00','','',33,'',0,4,'0000-00-00 00:00:00','0000-00-00 00:00:00','','');
/*!40000 ALTER TABLE `jos_banner` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `jos_bannerclient`
--

DROP TABLE IF EXISTS `jos_bannerclient`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `jos_bannerclient` (
  `cid` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(255) NOT NULL DEFAULT '',
  `contact` varchar(255) NOT NULL DEFAULT '',
  `email` varchar(255) NOT NULL DEFAULT '',
  `extrainfo` text NOT NULL,
  `checked_out` tinyint(1) NOT NULL DEFAULT '0',
  `checked_out_time` time DEFAULT NULL,
  `editor` varchar(50) DEFAULT NULL,
  PRIMARY KEY (`cid`)
) ENGINE=MyISAM AUTO_INCREMENT=2 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `jos_bannerclient`
--

LOCK TABLES `jos_bannerclient` WRITE;
/*!40000 ALTER TABLE `jos_bannerclient` DISABLE KEYS */;
INSERT INTO `jos_bannerclient` VALUES (1,'Open Source Matters','Administrator','admin@opensourcematters.org','',0,'00:00:00',NULL);
/*!40000 ALTER TABLE `jos_bannerclient` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `jos_bannertrack`
--

DROP TABLE IF EXISTS `jos_bannertrack`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `jos_bannertrack` (
  `track_date` date NOT NULL,
  `track_type` int(10) unsigned NOT NULL,
  `banner_id` int(10) unsigned NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `jos_bannertrack`
--

LOCK TABLES `jos_bannertrack` WRITE;
/*!40000 ALTER TABLE `jos_bannertrack` DISABLE KEYS */;
/*!40000 ALTER TABLE `jos_bannertrack` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `jos_categories`
--

DROP TABLE IF EXISTS `jos_categories`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `jos_categories` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `parent_id` int(11) NOT NULL DEFAULT '0',
  `title` varchar(255) NOT NULL DEFAULT '',
  `name` varchar(255) NOT NULL DEFAULT '',
  `alias` varchar(255) NOT NULL DEFAULT '',
  `image` varchar(255) NOT NULL DEFAULT '',
  `section` varchar(50) NOT NULL DEFAULT '',
  `image_position` varchar(30) NOT NULL DEFAULT '',
  `description` text NOT NULL,
  `published` tinyint(1) NOT NULL DEFAULT '0',
  `checked_out` int(11) unsigned NOT NULL DEFAULT '0',
  `checked_out_time` datetime NOT NULL DEFAULT '0000-00-00 00:00:00',
  `editor` varchar(50) DEFAULT NULL,
  `ordering` int(11) NOT NULL DEFAULT '0',
  `access` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `count` int(11) NOT NULL DEFAULT '0',
  `params` text NOT NULL,
  PRIMARY KEY (`id`),
  KEY `cat_idx` (`section`,`published`,`access`),
  KEY `idx_access` (`access`),
  KEY `idx_checkout` (`checked_out`)
) ENGINE=MyISAM AUTO_INCREMENT=36 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `jos_categories`
--

LOCK TABLES `jos_categories` WRITE;
/*!40000 ALTER TABLE `jos_categories` DISABLE KEYS */;
INSERT INTO `jos_categories` VALUES (1,0,'Latest','','latest-news','taking_notes.jpg','1','left','The latest news from the Joomla! Team',0,0,'0000-00-00 00:00:00','',1,0,1,''),(2,0,'Joomla! Specific Links','','joomla-specific-links','clock.jpg','com_weblinks','left','A selection of links that are all related to the Joomla! Project.',0,0,'0000-00-00 00:00:00',NULL,1,0,0,''),(3,0,'Newsflash','','newsflash','','1','left','',0,0,'0000-00-00 00:00:00','',2,0,0,''),(4,0,'Joomla!','','joomla','','com_newsfeeds','left','',1,0,'0000-00-00 00:00:00',NULL,2,0,0,''),(5,0,'Free and Open Source Software','','free-and-open-source-software','','com_newsfeeds','left','Read the latest news about free and open source software from some of its leading advocates.',1,0,'0000-00-00 00:00:00',NULL,3,0,0,''),(6,0,'Related Projects','','related-projects','','com_newsfeeds','left','Joomla builds on and collaborates with many other free and open source projects. Keep up with the latest news from some of them.',1,0,'0000-00-00 00:00:00',NULL,4,0,0,''),(12,0,'Contacts','','contacts','','com_contact_details','left','Contact Details for this Web site',0,62,'2009-10-25 13:55:08',NULL,0,0,0,''),(13,0,'Joomla','','joomla','','com_banner','left','',0,0,'0000-00-00 00:00:00',NULL,0,0,0,''),(14,0,'Text Ads','','text-ads','','com_banner','left','',0,0,'0000-00-00 00:00:00',NULL,0,0,0,''),(15,0,'Features','','features','','com_content','left','',0,0,'0000-00-00 00:00:00',NULL,6,0,0,''),(17,0,'Benefits','','benefits','','com_content','left','',0,0,'0000-00-00 00:00:00',NULL,4,0,0,''),(18,0,'Platforms','','platforms','','com_content','left','',0,0,'0000-00-00 00:00:00',NULL,3,0,0,''),(19,0,'Other Resources','','other-resources','','com_weblinks','left','',0,0,'0000-00-00 00:00:00',NULL,2,0,0,''),(29,0,'The CMS','','the-cms','','4','left','Information about the software behind Joomla!<br />',0,0,'0000-00-00 00:00:00',NULL,2,0,0,''),(28,0,'Current Users','','current-users','','3','left','Questions that users migrating to Joomla! 1.5 are likely to raise<br />',0,0,'0000-00-00 00:00:00',NULL,2,0,0,''),(25,0,'The Project','','the-project','','4','left','General facts about Joomla!<br />',0,0,'0000-00-00 00:00:00',NULL,1,0,0,''),(27,0,'New to Joomla!','','new-to-joomla','','3','left','Questions for new users of Joomla!',0,0,'0000-00-00 00:00:00',NULL,3,0,0,''),(30,0,'The Community','','the-community','','4','left','About the millions of Joomla! users and Web sites<br />',0,0,'0000-00-00 00:00:00',NULL,3,0,0,''),(31,0,'General','','general','','3','left','General questions about the Joomla! CMS',0,0,'0000-00-00 00:00:00',NULL,1,0,0,''),(32,0,'Languages','','languages','','3','left','Questions related to localisation and languages',0,0,'0000-00-00 00:00:00',NULL,4,0,0,''),(33,0,'Joomla! Promo','','joomla-promo','','com_banner','left','',0,0,'0000-00-00 00:00:00',NULL,1,0,0,''),(34,0,'All Contacts','','all-contacts','','com_contact_details','left','',1,62,'2009-10-25 13:55:30',NULL,1,0,0,''),(35,0,'Downloads','','downloads','','5','left','',1,0,'0000-00-00 00:00:00',NULL,1,0,0,'');
/*!40000 ALTER TABLE `jos_categories` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `jos_components`
--

DROP TABLE IF EXISTS `jos_components`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `jos_components` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(50) NOT NULL DEFAULT '',
  `link` varchar(255) NOT NULL DEFAULT '',
  `menuid` int(11) unsigned NOT NULL DEFAULT '0',
  `parent` int(11) unsigned NOT NULL DEFAULT '0',
  `admin_menu_link` varchar(255) NOT NULL DEFAULT '',
  `admin_menu_alt` varchar(255) NOT NULL DEFAULT '',
  `option` varchar(50) NOT NULL DEFAULT '',
  `ordering` int(11) NOT NULL DEFAULT '0',
  `admin_menu_img` varchar(255) NOT NULL DEFAULT '',
  `iscore` tinyint(4) NOT NULL DEFAULT '0',
  `params` text NOT NULL,
  `enabled` tinyint(4) NOT NULL DEFAULT '1',
  PRIMARY KEY (`id`),
  KEY `parent_option` (`parent`,`option`(32))
) ENGINE=MyISAM AUTO_INCREMENT=34 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `jos_components`
--

LOCK TABLES `jos_components` WRITE;
/*!40000 ALTER TABLE `jos_components` DISABLE KEYS */;
INSERT INTO `jos_components` VALUES (1,'Banners','',0,0,'','Banner Management','com_banners',0,'js/ThemeOffice/component.png',0,'track_impressions=0\ntrack_clicks=0\ntag_prefix=\n\n',1),(2,'Banners','',0,1,'option=com_banners','Active Banners','com_banners',1,'js/ThemeOffice/edit.png',0,'',1),(3,'Clients','',0,1,'option=com_banners&c=client','Manage Clients','com_banners',2,'js/ThemeOffice/categories.png',0,'',1),(4,'Web Links','option=com_weblinks',0,0,'','Manage Weblinks','com_weblinks',0,'js/ThemeOffice/component.png',0,'show_comp_description=1\ncomp_description=\nshow_link_hits=1\nshow_link_description=1\nshow_other_cats=1\nshow_headings=1\nshow_page_title=1\nlink_target=0\nlink_icons=\n\n',1),(5,'Links','',0,4,'option=com_weblinks','View existing weblinks','com_weblinks',1,'js/ThemeOffice/edit.png',0,'',1),(6,'Categories','',0,4,'option=com_categories&section=com_weblinks','Manage weblink categories','',2,'js/ThemeOffice/categories.png',0,'',1),(7,'Contacts','option=com_contact',0,0,'','Edit contact details','com_contact',0,'js/ThemeOffice/component.png',1,'contact_icons=0\nicon_address=\nicon_email=\nicon_telephone=\nicon_fax=\nicon_misc=\nshow_headings=1\nshow_position=1\nshow_email=0\nshow_telephone=1\nshow_mobile=1\nshow_fax=1\nbannedEmail=\nbannedSubject=\nbannedText=\nsession=1\ncustomReply=0\n\n',1),(8,'Contacts','',0,7,'option=com_contact','Edit contact details','com_contact',0,'js/ThemeOffice/edit.png',1,'',1),(9,'Categories','',0,7,'option=com_categories&section=com_contact_details','Manage contact categories','',2,'js/ThemeOffice/categories.png',1,'contact_icons=0\nicon_address=\nicon_email=\nicon_telephone=\nicon_fax=\nicon_misc=\nshow_headings=1\nshow_position=1\nshow_email=0\nshow_telephone=1\nshow_mobile=1\nshow_fax=1\nbannedEmail=\nbannedSubject=\nbannedText=\nsession=1\ncustomReply=0\n\n',1),(10,'Polls','option=com_poll',0,0,'option=com_poll','Manage Polls','com_poll',0,'js/ThemeOffice/component.png',0,'',1),(11,'News Feeds','option=com_newsfeeds',0,0,'','News Feeds Management','com_newsfeeds',0,'js/ThemeOffice/component.png',0,'',1),(12,'Feeds','',0,11,'option=com_newsfeeds','Manage News Feeds','com_newsfeeds',1,'js/ThemeOffice/edit.png',0,'show_headings=1\nshow_name=1\nshow_articles=1\nshow_link=1\nshow_cat_description=1\nshow_cat_items=1\nshow_feed_image=1\nshow_feed_description=1\nshow_item_description=1\nfeed_word_count=0\n\n',1),(13,'Categories','',0,11,'option=com_categories&section=com_newsfeeds','Manage Categories','',2,'js/ThemeOffice/categories.png',0,'',1),(14,'User','option=com_user',0,0,'','','com_user',0,'',1,'',1),(15,'Search','option=com_search',0,0,'option=com_search','Search Statistics','com_search',0,'js/ThemeOffice/component.png',1,'enabled=0\n\n',1),(16,'Categories','',0,1,'option=com_categories&section=com_banner','Categories','',3,'',1,'',1),(17,'Wrapper','option=com_wrapper',0,0,'','Wrapper','com_wrapper',0,'',1,'',1),(18,'Mail To','',0,0,'','','com_mailto',0,'',1,'',1),(19,'Media Manager','',0,0,'option=com_media','Media Manager','com_media',0,'',1,'upload_extensions=bmp,csv,doc,epg,gif,ico,jpg,odg,odp,ods,odt,pdf,png,ppt,swf,txt,xcf,xls,BMP,CSV,DOC,EPG,GIF,ICO,JPG,ODG,ODP,ODS,ODT,PDF,PNG,PPT,SWF,TXT,XCF,XLS,exe\nupload_maxsize=10000000\nfile_path=media\nimage_path=images/stories\nrestrict_uploads=1\nallowed_media_usergroup=3\ncheck_mime=1\nimage_extensions=bmp,gif,jpg,png\nignore_extensions=\nupload_mime=image/jpeg,image/gif,image/png,image/bmp,application/x-shockwave-flash,application/msword,application/excel,application/pdf,application/powerpoint,text/plain,application/x-zip\nupload_mime_illegal=text/html\nenable_flash=0\n\n',1),(20,'Articles','option=com_content',0,0,'','','com_content',0,'',1,'show_noauth=0\nshow_title=1\nlink_titles=0\nshow_intro=1\nshow_section=0\nlink_section=0\nshow_category=0\nlink_category=0\nshow_author=1\nshow_create_date=1\nshow_modify_date=1\nshow_item_navigation=0\nshow_readmore=1\nshow_vote=0\nshow_icons=1\nshow_pdf_icon=1\nshow_print_icon=1\nshow_email_icon=1\nshow_hits=1\nfeed_summary=0\n\n',1),(21,'Configuration Manager','',0,0,'','Configuration','com_config',0,'',1,'',1),(22,'Installation Manager','',0,0,'','Installer','com_installer',0,'',1,'',1),(23,'Language Manager','',0,0,'','Languages','com_languages',0,'',1,'',1),(24,'Mass mail','',0,0,'','Mass Mail','com_massmail',0,'',1,'mailSubjectPrefix=\nmailBodySuffix=\n\n',1),(25,'Menu Editor','',0,0,'','Menu Editor','com_menus',0,'',1,'',1),(27,'Messaging','',0,0,'','Messages','com_messages',0,'',1,'',1),(28,'Modules Manager','',0,0,'','Modules','com_modules',0,'',1,'',1),(29,'Plugin Manager','',0,0,'','Plugins','com_plugins',0,'',1,'',1),(30,'Template Manager','',0,0,'','Templates','com_templates',0,'',1,'',1),(31,'User Manager','',0,0,'','Users','com_users',0,'',1,'allowUserRegistration=0\nnew_usertype=Registered\nuseractivation=0\nfrontend_userparams=0\n\n',1),(32,'Cache Manager','',0,0,'','Cache','com_cache',0,'',1,'',1),(33,'Control Panel','',0,0,'','Control Panel','com_cpanel',0,'',1,'',1);
/*!40000 ALTER TABLE `jos_components` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `jos_contact_details`
--

DROP TABLE IF EXISTS `jos_contact_details`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `jos_contact_details` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(255) NOT NULL DEFAULT '',
  `alias` varchar(255) NOT NULL DEFAULT '',
  `con_position` varchar(255) DEFAULT NULL,
  `address` text,
  `suburb` varchar(100) DEFAULT NULL,
  `state` varchar(100) DEFAULT NULL,
  `country` varchar(100) DEFAULT NULL,
  `postcode` varchar(100) DEFAULT NULL,
  `telephone` varchar(255) DEFAULT NULL,
  `fax` varchar(255) DEFAULT NULL,
  `misc` mediumtext,
  `image` varchar(255) DEFAULT NULL,
  `imagepos` varchar(20) DEFAULT NULL,
  `email_to` varchar(255) DEFAULT NULL,
  `default_con` tinyint(1) unsigned NOT NULL DEFAULT '0',
  `published` tinyint(1) unsigned NOT NULL DEFAULT '0',
  `checked_out` int(11) unsigned NOT NULL DEFAULT '0',
  `checked_out_time` datetime NOT NULL DEFAULT '0000-00-00 00:00:00',
  `ordering` int(11) NOT NULL DEFAULT '0',
  `params` text NOT NULL,
  `user_id` int(11) NOT NULL DEFAULT '0',
  `catid` int(11) NOT NULL DEFAULT '0',
  `access` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `mobile` varchar(255) NOT NULL DEFAULT '',
  `webpage` varchar(255) NOT NULL DEFAULT '',
  PRIMARY KEY (`id`),
  KEY `catid` (`catid`)
) ENGINE=MyISAM AUTO_INCREMENT=3 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `jos_contact_details`
--

LOCK TABLES `jos_contact_details` WRITE;
/*!40000 ALTER TABLE `jos_contact_details` DISABLE KEYS */;
INSERT INTO `jos_contact_details` VALUES (1,'Name','name','Position','Street','Suburb','State','Country','Zip Code','Telephone','Fax','Miscellanous info','powered_by.png','top','email@email.com',1,0,0,'0000-00-00 00:00:00',1,'show_name=1\r\nshow_position=1\r\nshow_email=0\r\nshow_street_address=1\r\nshow_suburb=1\r\nshow_state=1\r\nshow_postcode=1\r\nshow_country=1\r\nshow_telephone=1\r\nshow_mobile=1\r\nshow_fax=1\r\nshow_webpage=1\r\nshow_misc=1\r\nshow_image=1\r\nallow_vcard=0\r\ncontact_icons=0\r\nicon_address=\r\nicon_email=\r\nicon_telephone=\r\nicon_fax=\r\nicon_misc=\r\nshow_email_form=1\r\nemail_description=1\r\nshow_email_copy=1\r\nbanned_email=\r\nbanned_subject=\r\nbanned_text=',0,12,0,'',''),(2,'Support','support','','','','','','','','','','',NULL,'filesearcher@atalantasoftware.com',0,1,0,'0000-00-00 00:00:00',1,'show_name=1\nshow_position=0\nshow_email=1\nshow_street_address=0\nshow_suburb=0\nshow_state=0\nshow_postcode=0\nshow_country=0\nshow_telephone=0\nshow_mobile=0\nshow_fax=0\nshow_webpage=0\nshow_misc=0\nshow_image=0\nallow_vcard=0\ncontact_icons=0\nicon_address=\nicon_email=\nicon_telephone=\nicon_mobile=\nicon_fax=\nicon_misc=\nshow_email_form=1\nemail_description=\nshow_email_copy=1\nbanned_email=\nbanned_subject=\nbanned_text=',62,34,0,'','');
/*!40000 ALTER TABLE `jos_contact_details` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `jos_content`
--

DROP TABLE IF EXISTS `jos_content`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `jos_content` (
  `id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `title` varchar(255) NOT NULL DEFAULT '',
  `alias` varchar(255) NOT NULL DEFAULT '',
  `title_alias` varchar(255) NOT NULL DEFAULT '',
  `introtext` mediumtext NOT NULL,
  `fulltext` mediumtext NOT NULL,
  `state` tinyint(3) NOT NULL DEFAULT '0',
  `sectionid` int(11) unsigned NOT NULL DEFAULT '0',
  `mask` int(11) unsigned NOT NULL DEFAULT '0',
  `catid` int(11) unsigned NOT NULL DEFAULT '0',
  `created` datetime NOT NULL DEFAULT '0000-00-00 00:00:00',
  `created_by` int(11) unsigned NOT NULL DEFAULT '0',
  `created_by_alias` varchar(255) NOT NULL DEFAULT '',
  `modified` datetime NOT NULL DEFAULT '0000-00-00 00:00:00',
  `modified_by` int(11) unsigned NOT NULL DEFAULT '0',
  `checked_out` int(11) unsigned NOT NULL DEFAULT '0',
  `checked_out_time` datetime NOT NULL DEFAULT '0000-00-00 00:00:00',
  `publish_up` datetime NOT NULL DEFAULT '0000-00-00 00:00:00',
  `publish_down` datetime NOT NULL DEFAULT '0000-00-00 00:00:00',
  `images` text NOT NULL,
  `urls` text NOT NULL,
  `attribs` text NOT NULL,
  `version` int(11) unsigned NOT NULL DEFAULT '1',
  `parentid` int(11) unsigned NOT NULL DEFAULT '0',
  `ordering` int(11) NOT NULL DEFAULT '0',
  `metakey` text NOT NULL,
  `metadesc` text NOT NULL,
  `access` int(11) unsigned NOT NULL DEFAULT '0',
  `hits` int(11) unsigned NOT NULL DEFAULT '0',
  `metadata` text NOT NULL,
  PRIMARY KEY (`id`),
  KEY `idx_section` (`sectionid`),
  KEY `idx_access` (`access`),
  KEY `idx_checkout` (`checked_out`),
  KEY `idx_state` (`state`),
  KEY `idx_catid` (`catid`),
  KEY `idx_createdby` (`created_by`)
) ENGINE=MyISAM AUTO_INCREMENT=56 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `jos_content`
--

LOCK TABLES `jos_content` WRITE;
/*!40000 ALTER TABLE `jos_content` DISABLE KEYS */;
INSERT INTO `jos_content` VALUES (1,'Welcome to Joomla!','welcome-to-joomla','','<div align=\"left\"><strong>Joomla! is a free open source framework and content publishing system designed for quickly creating highly interactive multi-language Web sites, online communities, media portals, blogs and eCommerce applications. <br /></strong></div><p><strong><br /></strong><img src=\"images/stories/powered_by.png\" border=\"0\" alt=\"Joomla! Logo\" title=\"Example Caption\" hspace=\"6\" vspace=\"0\" width=\"165\" height=\"68\" align=\"left\" />Joomla! provides an easy-to-use graphical user interface that simplifies the management and publishing of large volumes of content including HTML, documents, and rich media.  Joomla! is used by organisations of all sizes for intranets and extranets and is supported by a community of tens of thousands of users. </p>','With a fully documented library of developer resources, Joomla! allows the customisation of every aspect of a Web site including presentation, layout, administration, and the rapid integration with third-party applications.<p>Joomla! now provides more developer power while making the user experience all the more friendly. For those who always wanted increased extensibility, Joomla! 1.5 can make this happen.</p><p>A new framework, ground-up refactoring, and a highly-active development team brings the excitement of \'the next generation CMS\' to your fingertips.  Whether you are a systems architect or a complete \'noob\' Joomla! can take you to the next level of content delivery. \'More than a CMS\' is something we have been playing with as a catchcry because the new Joomla! API has such incredible power and flexibility, you are free to take whatever direction your creative mind takes you and Joomla! can help you get there so much more easily than ever before.</p><p>Thinking Web publishing? Think Joomla!</p>',1,1,0,1,'2008-08-12 10:00:00',62,'','2008-08-12 10:00:00',62,0,'0000-00-00 00:00:00','2006-01-03 01:00:00','0000-00-00 00:00:00','','','show_title=\nlink_titles=\nshow_intro=\nshow_section=\nlink_section=\nshow_category=\nlink_category=\nshow_vote=\nshow_author=\nshow_create_date=\nshow_modify_date=\nshow_pdf_icon=\nshow_print_icon=\nshow_email_icon=\nlanguage=\nkeyref=\nreadmore=',29,0,1,'','',0,92,'robots=\nauthor='),(2,'Newsflash 1','newsflash-1','','<p>Joomla! makes it easy to launch a Web site of any kind. Whether you want a brochure site or you are building a large online community, Joomla! allows you to deploy a new site in minutes and add extra functionality as you need it. The hundreds of available Extensions will help to expand your site and allow you to deliver new services that extend your reach into the Internet.</p>','',1,1,0,3,'2008-08-10 06:30:34',62,'','2008-08-10 06:30:34',62,0,'0000-00-00 00:00:00','2004-08-09 10:00:00','0000-00-00 00:00:00','','','show_title=\nlink_titles=\nshow_intro=\nshow_section=\nlink_section=\nshow_category=\nlink_category=\nshow_vote=\nshow_author=\nshow_create_date=\nshow_modify_date=\nshow_pdf_icon=\nshow_print_icon=\nshow_email_icon=\nlanguage=\nkeyref=\nreadmore=',7,0,3,'','',0,1,'robots=\nauthor='),(3,'Newsflash 2','newsflash-2','','<p>The one thing about a Web site, it always changes! Joomla! makes it easy to add Articles, content, images, videos, and more. Site administrators can edit and manage content \'in-context\' by clicking the \'Edit\' link. Webmasters can also edit content through a graphical Control Panel that gives you complete control over your site.</p>','',1,1,0,3,'2008-08-09 22:30:34',62,'','2008-08-09 22:30:34',62,0,'0000-00-00 00:00:00','2004-08-09 06:00:00','0000-00-00 00:00:00','','','show_title=\nlink_titles=\nshow_intro=\nshow_section=\nlink_section=\nshow_category=\nlink_category=\nshow_vote=\nshow_author=\nshow_create_date=\nshow_modify_date=\nshow_pdf_icon=\nshow_print_icon=\nshow_email_icon=\nlanguage=\nkeyref=\nreadmore=',6,0,4,'','',0,0,'robots=\nauthor='),(4,'Newsflash 3','newsflash-3','','<p>With a library of thousands of free <a href=\"http://extensions.joomla.org\" target=\"_blank\" title=\"The Joomla! Extensions Directory\">Extensions</a>, you can add what you need as your site grows. Don\'t wait, look through the <a href=\"http://extensions.joomla.org/\" target=\"_blank\" title=\"Joomla! Extensions\">Joomla! Extensions</a>  library today. </p>','',1,1,0,3,'2008-08-10 06:30:34',62,'','2008-08-10 06:30:34',62,0,'0000-00-00 00:00:00','2004-08-09 10:00:00','0000-00-00 00:00:00','','','show_title=\nlink_titles=\nshow_intro=\nshow_section=\nlink_section=\nshow_category=\nlink_category=\nshow_vote=\nshow_author=\nshow_create_date=\nshow_modify_date=\nshow_pdf_icon=\nshow_print_icon=\nshow_email_icon=\nlanguage=\nkeyref=\nreadmore=',7,0,5,'','',0,1,'robots=\nauthor='),(5,'Joomla! License Guidelines','joomla-license-guidelines','joomla-license-guidelines','<p>This Web site is powered by <a href=\"http://joomla.org/\" target=\"_blank\" title=\"Joomla!\">Joomla!</a> The software and default templates on which it runs are Copyright 2005-2008 <a href=\"http://www.opensourcematters.org/\" target=\"_blank\" title=\"Open Source Matters\">Open Source Matters</a>. The sample content distributed with Joomla! is licensed under the <a href=\"http://docs.joomla.org/JEDL\" target=\"_blank\" title=\"Joomla! Electronic Document License\">Joomla! Electronic Documentation License.</a> All data entered into this Web site and templates added after installation, are copyrighted by their respective copyright owners.</p> <p>If you want to distribute, copy, or modify Joomla!, you are welcome to do so under the terms of the <a href=\"http://www.gnu.org/licenses/old-licenses/gpl-2.0.html#SEC1\" target=\"_blank\" title=\"GNU General Public License\"> GNU General Public License</a>. If you are unfamiliar with this license, you might want to read <a href=\"http://www.gnu.org/licenses/old-licenses/gpl-2.0.html#SEC4\" target=\"_blank\" title=\"How To Apply These Terms To Your Program\">\'How To Apply These Terms To Your Program\'</a> and the <a href=\"http://www.gnu.org/licenses/old-licenses/gpl-2.0-faq.html\" target=\"_blank\" title=\"GNU General Public License FAQ\">\'GNU General Public License FAQ\'</a>.</p> <p>The Joomla! licence has always been GPL.</p>','',0,4,0,25,'2008-08-20 10:11:07',62,'','2008-08-20 10:11:07',62,0,'0000-00-00 00:00:00','2004-08-19 06:00:00','0000-00-00 00:00:00','','','show_title=\nlink_titles=\nshow_intro=\nshow_section=\nlink_section=\nshow_category=\nlink_category=\nshow_vote=\nshow_author=\nshow_create_date=\nshow_modify_date=\nshow_pdf_icon=\nshow_print_icon=\nshow_email_icon=\nlanguage=\nkeyref=\nreadmore=',7,0,2,'','',0,100,'robots=\nauthor='),(6,'We are Volunteers','we-are-volunteers','','<p>The Joomla Core Team and Working Group members are volunteer developers, designers, administrators and managers who have worked together to take Joomla! to new heights in its relatively short life. Joomla! has some wonderfully talented people taking Open Source concepts to the forefront of industry standards.  Joomla! 1.5 is a major leap forward and represents the most exciting Joomla! release in the history of the project. </p>','',0,1,0,1,'2007-07-07 09:54:06',62,'','2007-07-07 09:54:06',62,0,'0000-00-00 00:00:00','2004-07-06 22:00:00','0000-00-00 00:00:00','','','show_title=\nlink_titles=\nshow_intro=\nshow_section=\nlink_section=\nshow_category=\nlink_category=\nshow_vote=\nshow_author=\nshow_create_date=\nshow_modify_date=\nshow_pdf_icon=\nshow_print_icon=\nshow_email_icon=\nlanguage=\nkeyref=\nreadmore=',10,0,4,'','',0,54,'robots=\nauthor='),(9,'Millions of Smiles','millions-of-smiles','','<p>The Joomla! team has millions of good reasons to be smiling about the Joomla! 1.5. In its current incarnation, it\'s had millions of downloads, taking it to an unprecedented level of popularity.  The new code base is almost an entire re-factor of the old code base.  The user experience is still extremely slick but for developers the API is a dream.  A proper framework for real PHP architects seeking the best of the best.</p><p>If you\'re a former Mambo User or a 1.0 series Joomla! User, 1.5 is the future of CMSs for a number of reasons.  It\'s more powerful, more flexible, more secure, and intuitive.  Our developers and interface designers have worked countless hours to make this the most exciting release in the content management system sphere.</p><p>Go on ... get your FREE copy of Joomla! today and spread the word about this benchmark project. </p>','',0,1,0,1,'2007-07-07 09:54:06',62,'','2007-07-07 09:54:06',62,0,'0000-00-00 00:00:00','2004-07-06 22:00:00','0000-00-00 00:00:00','','','show_title=\nlink_titles=\nshow_intro=\nshow_section=\nlink_section=\nshow_category=\nlink_category=\nshow_vote=\nshow_author=\nshow_create_date=\nshow_modify_date=\nshow_pdf_icon=\nshow_print_icon=\nshow_email_icon=\nlanguage=\nkeyref=\nreadmore=',5,0,7,'','',0,23,'robots=\nauthor='),(10,'How do I localise Joomla! to my language?','how-do-i-localise-joomla-to-my-language','','<h4>General<br /></h4><p>In Joomla! 1.5 all User interfaces can be localised. This includes the installation, the Back-end Control Panel and the Front-end Site.</p><p>The core release of Joomla! 1.5 is shipped with multiple language choices in the installation but, other than English (the default), languages for the Site and Administration interfaces need to be added after installation. Links to such language packs exist below.</p>','<p>Translation Teams for Joomla! 1.5 may have also released fully localised installation packages where site, administrator and sample data are in the local language. These localised releases can be found in the specific team projects on the <a href=\"http://extensions.joomla.org/component/option,com_mtree/task,listcats/cat_id,1837/Itemid,35/\" target=\"_blank\" title=\"JED\">Joomla! Extensions Directory</a>.</p><h4>How do I install language packs?</h4><ul><li>First download both the admin and the site language packs that you require.</li><li>Install each pack separately using the Extensions-&gt;Install/Uninstall Menu selection and then the package file upload facility.</li><li>Go to the Language Manager and be sure to select Site or Admin in the sub-menu. Then select the appropriate language and make it the default one using the Toolbar button.</li></ul><h4>How do I select languages?</h4><ul><li>Default languages can be independently set for Site and for Administrator</li><li>In addition, users can define their preferred language for each Site and Administrator. This takes affect after logging in.</li><li>While logging in to the Administrator Back-end, a language can also be selected for the particular session.</li></ul><h4>Where can I find Language Packs and Localised Releases?</h4><p><em>Please note that Joomla! 1.5 is new and language packs for this version may have not been released at this time.</em> </p><ul><li><a href=\"http://joomlacode.org/gf/project/jtranslation/\" target=\"_blank\" title=\"Accredited Translations\">The Joomla! Accredited Translations Project</a>  - This is a joint repository for language packs that were developed by teams that are members of the Joomla! Translations Working Group.</li><li><a href=\"http://extensions.joomla.org/component/option,com_mtree/task,listcats/cat_id,1837/Itemid,35/\" target=\"_blank\" title=\"Translations\">The Joomla! Extensions Site - Translations</a>  </li><li><a href=\"http://community.joomla.org/translations.html\" target=\"_blank\" title=\"Translation Work Group Teams\">List of Translation Teams and Translation Partner Sites for Joomla! 1.5</a> </li></ul>',1,3,0,32,'2008-07-30 14:06:37',62,'','2008-07-30 14:06:37',62,0,'0000-00-00 00:00:00','2006-09-29 10:00:00','0000-00-00 00:00:00','','','show_title=\nlink_titles=\nshow_intro=\nshow_section=\nlink_section=\nshow_category=\nlink_category=\nshow_vote=\nshow_author=\nshow_create_date=\nshow_modify_date=\nshow_pdf_icon=\nshow_print_icon=\nshow_email_icon=\nlanguage=\nkeyref=\nreadmore=',9,0,5,'','',0,10,'robots=\nauthor='),(11,'How do I upgrade to Joomla! 1.5 ?','how-do-i-upgrade-to-joomla-15','','<p>Joomla! 1.5 does not provide an upgrade path from earlier versions. Converting an older site to a Joomla! 1.5 site requires creation of a new empty site using Joomla! 1.5 and then populating the new site with the content from the old site. This migration of content is not a one-to-one process and involves conversions and modifications to the content dump.</p> <p>There are two ways to perform the migration:</p>',' <div id=\"post_content-107\"><li>An automated method of migration has been provided which uses a migrator Component to create the migration dump out of the old site (Mambo 4.5.x up to Joomla! 1.0.x) and a smart import facility in the Joomla! 1.5 Installation that performs required conversions and modifications during the installation process.</li> <li>Migration can be performed manually. This involves exporting the required tables, manually performing required conversions and modifications and then importing the content to the new site after it is installed.</li>  <p><!--more--></p> <h2><strong> Automated migration</strong></h2>  <p>This is a two phased process using two tools. The first tool is a migration Component named <font face=\"courier new,courier\">com_migrator</font>. This Component has been contributed by Harald Baer and is based on his <strong>eBackup </strong>Component. The migrator needs to be installed on the old site and when activated it prepares the required export dump of the old site\'s data. The second tool is built into the Joomla! 1.5 installation process. The exported content dump is loaded to the new site and all conversions and modification are performed on-the-fly.</p> <h3><u> Step 1 - Using com_migrator to export data from old site:</u></h3> <li>Install the <font face=\"courier new,courier\">com_migrator</font> Component on the <u><strong>old</strong></u> site. It can be found at the <a href=\"http://joomlacode.org/gf/project/pasamioprojects/frs/\" target=\"_blank\" title=\"JoomlaCode\">JoomlaCode developers forge</a>.</li> <li>Select the Component in the Component Menu of the Control Panel.</li> <li>Click on the <strong>Dump it</strong> icon. Three exported <em>gzipped </em>export scripts will be created. The first is a complete backup of the old site. The second is the migration content of all core elements which will be imported to the new site. The third is a backup of all 3PD Component tables.</li> <li>Click on the download icon of the particular exports files needed and store locally.</li> <li>Multiple export sets can be created.</li> <li>The exported data is not modified in anyway and the original encoding is preserved. This makes the <font face=\"courier new,courier\">com_migrator</font> tool a recommended tool to use for manual migration as well.</li> <h3><u> Step 2 - Using the migration facility to import and convert data during Joomla! 1.5 installation:</u></h3><p>Note: This function requires the use of the <em><font face=\"courier new,courier\">iconv </font></em>function in PHP to convert encodings. If <em><font face=\"courier new,courier\">iconv </font></em>is not found a warning will be provided.</p> <li>In step 6 - Configuration select the \'Load Migration Script\' option in the \'Load Sample Data, Restore or Migrate Backed Up Content\' section of the page.</li> <li>Enter the table prefix used in the content dump. For example: \'jos_\' or \'site2_\' are acceptable values.</li> <li>Select the encoding of the dumped content in the dropdown list. This should be the encoding used on the pages of the old site. (As defined in the _ISO variable in the language file or as seen in the browser page info/encoding/source)</li> <li>Browse the local host and select the migration export and click on <strong>Upload and Execute</strong></li> <li>A success message should appear or alternately a listing of database errors</li> <li>Complete the other required fields in the Configuration step such as Site Name and Admin details and advance to the final step of installation. (Admin details will be ignored as the imported data will take priority. Please remember admin name and password from the old site)</li> <p><u><br /></u></p></div>',0,3,0,28,'2008-07-30 20:27:52',62,'','2008-07-30 20:27:52',62,0,'0000-00-00 00:00:00','2006-09-29 12:00:00','0000-00-00 00:00:00','','','show_title=\nlink_titles=\nshow_intro=\nshow_section=\nlink_section=\nshow_category=\nlink_category=\nshow_vote=\nshow_author=\nshow_create_date=\nshow_modify_date=\nshow_pdf_icon=\nshow_print_icon=\nshow_email_icon=\nlanguage=\nkeyref=\nreadmore=',10,0,3,'','',0,14,'robots=\nauthor='),(12,'Why does Joomla! 1.5 use UTF-8 encoding?','why-does-joomla-15-use-utf-8-encoding','','<p>Well... how about never needing to mess with encoding settings again?</p><p>Ever needed to display several languages on one page or site and something always came up in Giberish?</p><p>With utf-8 (a variant of Unicode) glyphs (character forms) of basically all languages can be displayed with one single encoding setting. </p>','',1,3,0,31,'2008-08-05 01:11:29',62,'','2008-08-05 01:11:29',62,0,'0000-00-00 00:00:00','2006-10-03 10:00:00','0000-00-00 00:00:00','','','show_title=\nlink_titles=\nshow_intro=\nshow_section=\nlink_section=\nshow_category=\nlink_category=\nshow_vote=\nshow_author=\nshow_create_date=\nshow_modify_date=\nshow_pdf_icon=\nshow_print_icon=\nshow_email_icon=\nlanguage=\nkeyref=\nreadmore=',8,0,8,'','',0,29,'robots=\nauthor='),(13,'What happened to the locale setting?','what-happened-to-the-locale-setting','','This is now defined in the Language [<em>lang</em>].xml file in the Language metadata settings. If you are having locale problems such as dates do not appear in your language for example, you might want to check/edit the entries in the locale tag. Note that multiple locale strings can be set and the host will usually accept the first one recognised.','',0,3,0,28,'2008-08-06 16:47:35',62,'','2008-08-06 16:47:35',62,0,'0000-00-00 00:00:00','2006-10-05 14:00:00','0000-00-00 00:00:00','','','show_title=\nlink_titles=\nshow_intro=\nshow_section=\nlink_section=\nshow_category=\nlink_category=\nshow_vote=\nshow_author=\nshow_create_date=\nshow_modify_date=\nshow_pdf_icon=\nshow_print_icon=\nshow_email_icon=\nlanguage=\nkeyref=\nreadmore=',7,0,2,'','',0,11,'robots=\nauthor='),(14,'What is the FTP layer for?','what-is-the-ftp-layer-for','','<p>The FTP Layer allows file operations (such as installing Extensions or updating the main configuration file) without having to make all the folders and files writable. This has been an issue on Linux and other Unix based platforms in respect of file permissions. This makes the site admin\'s life a lot easier and increases security of the site.</p><p>You can check the write status of relevent folders by going to \'\'Help-&gt;System Info\" and then in the sub-menu to \"Directory Permissions\". With the FTP Layer enabled even if all directories are red, Joomla! will operate smoothly.</p><p>NOTE: the FTP layer is not required on a Windows host/server. </p>','',1,3,0,31,'2008-08-06 21:27:49',62,'','2008-08-06 21:27:49',62,0,'0000-00-00 00:00:00','2006-10-05 16:00:00','0000-00-00 00:00:00','','','show_title=\nlink_titles=\nshow_intro=\nshow_section=\nlink_section=\nshow_category=\nlink_category=\nshow_vote=\nshow_author=\nshow_create_date=\nshow_modify_date=\nshow_pdf_icon=\nshow_print_icon=\nshow_email_icon=\nlanguage=\nkeyref=',6,0,6,'','',0,23,'robots=\nauthor='),(15,'Can Joomla! 1.5 operate with PHP Safe Mode On?','can-joomla-15-operate-with-php-safe-mode-on','','<p>Yes it can! This is a significant security improvement.</p><p>The <em>safe mode</em> limits PHP to be able to perform actions only on files/folders who\'s owner is the same as PHP is currently using (this is usually \'apache\'). As files normally are created either by the Joomla! application or by FTP access, the combination of PHP file actions and the FTP Layer allows Joomla! to operate in PHP Safe Mode.</p>','',1,3,0,31,'2008-08-06 19:28:35',62,'','2008-08-06 19:28:35',62,0,'0000-00-00 00:00:00','2006-10-05 14:00:00','0000-00-00 00:00:00','','','show_title=\nlink_titles=\nshow_intro=\nshow_section=\nlink_section=\nshow_category=\nlink_category=\nshow_vote=\nshow_author=\nshow_create_date=\nshow_modify_date=\nshow_pdf_icon=\nshow_print_icon=\nshow_email_icon=\nlanguage=\nkeyref=\nreadmore=',7,0,4,'','',0,8,'robots=\nauthor='),(16,'Only one edit window! How do I create \"Read more...\"?','only-one-edit-window-how-do-i-create-read-more','','<p>This is now implemented by inserting a <strong>Read more...</strong> tag (the button is located below the editor area) a dotted line appears in the edited text showing the split location for the <em>Read more....</em> A new Plugin takes care of the rest.</p><p>It is worth mentioning that this does not have a negative effect on migrated data from older sites. The new implementation is fully backward compatible.</p>','',0,3,0,28,'2008-08-06 19:29:28',62,'','2008-08-06 19:29:28',62,0,'0000-00-00 00:00:00','2006-10-05 14:00:00','0000-00-00 00:00:00','','','show_title=\nlink_titles=\nshow_intro=\nshow_section=\nlink_section=\nshow_category=\nlink_category=\nshow_vote=\nshow_author=\nshow_create_date=\nshow_modify_date=\nshow_pdf_icon=\nshow_print_icon=\nshow_email_icon=\nlanguage=\nkeyref=\nreadmore=',7,0,4,'','',0,20,'robots=\nauthor='),(17,'My MySQL database does not support UTF-8. Do I have a problem?','my-mysql-database-does-not-support-utf-8-do-i-have-a-problem','','No you don\'t. Versions of MySQL lower than 4.1 do not have built in UTF-8 support. However, Joomla! 1.5 has made provisions for backward compatibility and is able to use UTF-8 on older databases. Let the installer take care of all the settings and there is no need to make any changes to the database (charset, collation, or any other).','',1,3,0,31,'2008-08-07 09:30:37',62,'','2008-08-07 09:30:37',62,0,'0000-00-00 00:00:00','2006-10-05 20:00:00','0000-00-00 00:00:00','','','show_title=\nlink_titles=\nshow_intro=\nshow_section=\nlink_section=\nshow_category=\nlink_category=\nshow_vote=\nshow_author=\nshow_create_date=\nshow_modify_date=\nshow_pdf_icon=\nshow_print_icon=\nshow_email_icon=\nlanguage=\nkeyref=\nreadmore=',10,0,7,'','',0,9,'robots=\nauthor='),(18,'Joomla! Features','joomla-features','','<h4><font color=\"#ff6600\">Joomla! features:</font></h4> <ul><li>Completely database driven site engines </li><li>News, products, or services sections fully editable and manageable</li><li>Topics sections can be added to by contributing Authors </li><li>Fully customisable layouts including <em>left</em>, <em>center</em>, and <em>right </em>Menu boxes </li><li>Browser upload of images to your own library for use anywhere in the site </li><li>Dynamic Forum/Poll/Voting booth for on-the-spot results </li><li>Runs on Linux, FreeBSD, MacOSX server, Solaris, and AIX','  </li></ul> <h4>Extensive Administration:</h4> <ul><li>Change order of objects including news, FAQs, Articles etc. </li><li>Random Newsflash generator </li><li>Remote Author submission Module for News, Articles, FAQs, and Links </li><li>Object hierarchy - as many Sections, departments, divisions, and pages as you want </li><li>Image library - store all your PNGs, PDFs, DOCs, XLSs, GIFs, and JPEGs online for easy use </li><li>Automatic Path-Finder. Place a picture and let Joomla! fix the link </li><li>News Feed Manager. Easily integrate news feeds into your Web site.</li><li>E-mail a friend and Print format available for every story and Article </li><li>In-line Text editor similar to any basic word processor software </li><li>User editable look and feel </li><li>Polls/Surveys - Now put a different one on each page </li><li>Custom Page Modules. Download custom page Modules to spice up your site </li><li>Template Manager. Download Templates and implement them in seconds </li><li>Layout preview. See how it looks before going live </li><li>Banner Manager. Make money out of your site.</li></ul>',0,4,0,29,'2008-08-08 23:32:45',62,'','2008-08-08 23:32:45',62,0,'0000-00-00 00:00:00','2006-10-07 06:00:00','0000-00-00 00:00:00','','','show_title=\nlink_titles=\nshow_intro=\nshow_section=\nlink_section=\nshow_category=\nlink_category=\nshow_vote=\nshow_author=\nshow_create_date=\nshow_modify_date=\nshow_pdf_icon=\nshow_print_icon=\nshow_email_icon=\nlanguage=\nkeyref=\nreadmore=',11,0,4,'','',0,59,'robots=\nauthor='),(19,'Joomla! Overview','joomla-overview','','<p>If you\'re new to Web publishing systems, you\'ll find that Joomla! delivers sophisticated solutions to your online needs. It can deliver a robust enterprise-level Web site, empowered by endless extensibility for your bespoke publishing needs. Moreover, it is often the system of choice for small business or home users who want a professional looking site that\'s simple to deploy and use. <em>We do content right</em>.<br /> </p><p>So what\'s the catch? How much does this system cost?</p><p> Well, there\'s good news ... and more good news! Joomla! 1.5 is free, it is released under an Open Source license - the GNU/General Public License v 2.0. Had you invested in a mainstream, commercial alternative, there\'d be nothing but moths left in your wallet and to add new functionality would probably mean taking out a second mortgage each time you wanted something adding!</p><p>Joomla! changes all that ... <br />Joomla! is different from the normal models for content management software. For a start, it\'s not complicated. Joomla! has been developed for everybody, and anybody can develop it further. It is designed to work (primarily) with other Open Source, free, software such as PHP, MySQL, and Apache. </p><p>It is easy to install and administer, and is reliable. </p><p>Joomla! doesn\'t even require the user or administrator of the system to know HTML to operate it once it\'s up and running.</p><p>To get the perfect Web site with all the functionality that you require for your particular application may take additional time and effort, but with the Joomla! Community support that is available and the many Third Party Developers actively creating and releasing new Extensions for the 1.5 platform on an almost daily basis, there is likely to be something out there to meet your needs. Or you could develop your own Extensions and make these available to the rest of the community. </p>','',0,4,0,29,'2008-08-09 07:49:20',62,'','2008-08-09 07:49:20',62,0,'0000-00-00 00:00:00','2006-10-07 10:00:00','0000-00-00 00:00:00','','','show_title=\nlink_titles=\nshow_intro=\nshow_section=\nlink_section=\nshow_category=\nlink_category=\nshow_vote=\nshow_author=\nshow_create_date=\nshow_modify_date=\nshow_pdf_icon=\nshow_print_icon=\nshow_email_icon=\nlanguage=\nkeyref=\nreadmore=',13,0,2,'','',0,153,'robots=\nauthor='),(20,'Support and Documentation','support-and-documentation','','<h1>Support </h1><p>Support for the Joomla! CMS can be found on several places. The best place to start would be the <a href=\"http://docs.joomla.org/\" target=\"_blank\" title=\"Joomla! Official Documentation Wiki\">Joomla! Official Documentation Wiki</a>. Here you can help yourself to the information that is regularly published and updated as Joomla! develops. There is much more to come too!</p> <p>Of course you should not forget the Help System of the CMS itself. On the <em>topmenu </em>in the Back-end Control panel you find the Help button which will provide you with lots of explanation on features.</p> <p>Another great place would of course be the <a href=\"http://forum.joomla.org/\" target=\"_blank\" title=\"Forum\">Forum</a> . On the Joomla! Forum you can find help and support from Community members as well as from Joomla! Core members and Working Group members. The forum contains a lot of information, FAQ\'s, just about anything you are looking for in terms of support.</p> <p>Two other resources for Support are the <a href=\"http://developer.joomla.org/\" target=\"_blank\" title=\"Joomla! Developer Site\">Joomla! Developer Site</a> and the <a href=\"http://extensions.joomla.org/\" target=\"_blank\" title=\"Joomla! Extensions Directory\">Joomla! Extensions Directory</a> (JED). The Joomla! Developer Site provides lots of technical information for the experienced Developer as well as those new to Joomla! and development work in general. The JED whilst not a support site in the strictest sense has many of the Extensions that you will need as you develop your own Web site.</p> <p>The Joomla! Developers and Bug Squad members are regularly posting their blog reports about several topics such as programming techniques and security issues.</p> <h1>Documentation</h1> <p>Joomla! Documentation can of course be found on the <a href=\"http://docs.joomla.org/\" target=\"_blank\" title=\"Joomla! Official Documentation Wiki\">Joomla! Official Documentation Wiki</a>. You can find information for beginners, installation, upgrade, Frequently Asked Questions, developer topics, and a lot more. The Documentation Team helps oversee the wiki but you are invited to contribute content, as well.</p> <p>There are also books written about Joomla! You can find a listing of these books in the <a href=\"http://shop.joomla.org/\" target=\"_blank\" title=\"Joomla! Shop\">Joomla! Shop</a>.</p>','',0,4,0,25,'2008-08-09 08:33:57',62,'','2008-08-09 08:33:57',62,0,'0000-00-00 00:00:00','2006-10-07 10:00:00','0000-00-00 00:00:00','','','show_title=\nlink_titles=\nshow_intro=\nshow_section=\nlink_section=\nshow_category=\nlink_category=\nshow_vote=\nshow_author=\nshow_create_date=\nshow_modify_date=\nshow_pdf_icon=\nshow_print_icon=\nshow_email_icon=\nlanguage=\nkeyref=\nreadmore=',13,0,1,'','',0,6,'robots=\nauthor='),(21,'Joomla! Facts','joomla-facts','','<p>Here are some interesting facts about Joomla!</p><ul><li><span>Over 210,000 active registered Users on the <a href=\"http://forum.joomla.org\" target=\"_blank\" title=\"Joomla Forums\">Official Joomla! community forum</a> and more on the many international community sites.</span><ul><li><span>over 1,000,000 posts in over 200,000 topics</span></li><li>over 1,200 posts per day</li><li>growing at 150 new participants each day!</li></ul></li><li><span>1168 Projects on the JoomlaCode (<a href=\"http://joomlacode.org/\" target=\"_blank\" title=\"JoomlaCode\">joomlacode.org</a> ). All for open source addons by third party developers.</span><ul><li><span>Well over 6,000,000 downloads of Joomla! since the migration to JoomlaCode in March 2007.<br /></span></li></ul></li><li><span>Nearly 4,000 extensions for Joomla! have been registered on the <a href=\"http://extensions.joomla.org\" target=\"_blank\" title=\"http://extensions.joomla.org\">Joomla! Extension Directory</a>  </span></li><li><span>Joomla.org exceeds 2 TB of traffic per month!</span></li></ul>','',0,4,0,30,'2008-08-09 16:46:37',62,'','2008-08-09 16:46:37',62,0,'0000-00-00 00:00:00','2006-10-07 14:00:00','0000-00-00 00:00:00','','','show_title=\nlink_titles=\nshow_intro=\nshow_section=\nlink_section=\nshow_category=\nlink_category=\nshow_vote=\nshow_author=\nshow_create_date=\nshow_modify_date=\nshow_pdf_icon=\nshow_print_icon=\nshow_email_icon=\nlanguage=\nkeyref=\nreadmore=',13,0,1,'','',0,50,'robots=\nauthor='),(22,'What\'s New in 1.5?','whats-new-in-15','','<p>As with previous releases, Joomla! provides a unified and easy-to-use framework for delivering content for Web sites of all kinds. To support the changing nature of the Internet and emerging Web technologies, Joomla! required substantial restructuring of its core functionality and we also used this effort to simplify many challenges within the current user interface. Joomla! 1.5 has many new features.</p>','<p style=\"margin-bottom: 0in\">In Joomla! 1.5, you\'ll notice: </p>    <ul><li>     <p style=\"margin-bottom: 0in\">       Substantially improved usability, manageability, and scalability far beyond the original Mambo foundations</p>   </li><li>     <p style=\"margin-bottom: 0in\"> Expanded accessibility to support internationalisation, double-byte characters and right-to-left support for Arabic, Farsi, and Hebrew languages among others</p>   </li><li>     <p style=\"margin-bottom: 0in\"> Extended integration of external applications through Web services and remote authentication such as the Lightweight Directory Access Protocol (LDAP)</p>   </li><li>     <p style=\"margin-bottom: 0in\"> Enhanced content delivery, template and presentation capabilities to support accessibility standards and content delivery to any destination</p>   </li><li>     <p style=\"margin-bottom: 0in\">       A more sustainable and flexible framework for Component and Extension developers</p>   </li><li>     <p style=\"margin-bottom: 0in\">Backward compatibility with previous releases of Components, Templates, Modules, and other Extensions</p></li></ul>',0,4,0,29,'2008-08-11 22:13:58',62,'','2008-08-11 22:13:58',62,0,'0000-00-00 00:00:00','2006-10-10 18:00:00','0000-00-00 00:00:00','','','show_title=\nlink_titles=\nshow_intro=\nshow_section=\nlink_section=\nshow_category=\nlink_category=\nshow_vote=\nshow_author=\nshow_create_date=\nshow_modify_date=\nshow_pdf_icon=\nshow_print_icon=\nshow_email_icon=\nlanguage=\nkeyref=\nreadmore=',10,0,1,'','',0,92,'robots=\nauthor='),(23,'Platforms and Open Standards','platforms-and-open-standards','','<p class=\"MsoNormal\">Joomla! runs on any platform including Windows, most flavours of Linux, several Unix versions, and the Apple OS/X platform.  Joomla! depends on PHP and the MySQL database to deliver dynamic content.  </p>            <p class=\"MsoNormal\">The minimum requirements are:</p>      <ul><li>Apache 1.x, 2.x and higher</li><li>PHP 4.3 and higher</li><li>MySQL 3.23 and higher</li></ul>It will also run on alternative server platforms such as Windows IIS - provided they support PHP and MySQL - but these require additional configuration in order for the Joomla! core package to be successful installed and operated.','',0,4,0,25,'2008-08-11 04:22:14',62,'','2008-08-11 04:22:14',62,0,'0000-00-00 00:00:00','2006-10-10 08:00:00','0000-00-00 00:00:00','','','show_title=\nlink_titles=\nshow_intro=\nshow_section=\nlink_section=\nshow_category=\nlink_category=\nshow_vote=\nshow_author=\nshow_create_date=\nshow_modify_date=\nshow_pdf_icon=\nshow_print_icon=\nshow_email_icon=\nlanguage=\nkeyref=\nreadmore=',7,0,3,'','',0,11,'robots=\nauthor='),(24,'Content Layouts','content-layouts','','<p>Joomla! provides plenty of flexibility when displaying your Web content. Whether you are using Joomla! for a blog site, news or a Web site for a company, you\'ll find one or more content styles to showcase your information. You can also change the style of content dynamically depending on your preferences. Joomla! calls how a page is laid out a <strong>layout</strong>. Use the guide below to understand which layouts are available and how you might use them. </p> <h2>Content </h2> <p>Joomla! makes it extremely easy to add and display content. All content  is placed where your mainbody tag in your template is located. There are three main types of layouts available in Joomla! and all of them can be customised via parameters. The display and parameters are set in the Menu Item used to display the content your working on. You create these layouts by creating a Menu Item and choosing how you want the content to display.</p> <h3>Blog Layout<br /> </h3> <p>Blog layout will show a listing of all Articles of the selected blog type (Section or Category) in the mainbody position of your template. It will give you the standard title, and Intro of each Article in that particular Category and/or Section. You can customise this layout via the use of the Preferences and Parameters, (See Article Parameters) this is done from the Menu not the Section Manager!</p> <h3>Blog Archive Layout<br /> </h3> <p>A Blog Archive layout will give you a similar output of Articles as the normal Blog Display but will add, at the top, two drop down lists for month and year plus a search button to allow Users to search for all Archived Articles from a specific month and year.</p> <h3>List Layout<br /> </h3> <p>Table layout will simply give you a <em>tabular </em>list<em> </em>of all the titles in that particular Section or Category. No Intro text will be displayed just the titles. You can set how many titles will be displayed in this table by Parameters. The table layout will also provide a filter Section so that Users can reorder, filter, and set how many titles are listed on a single page (up to 50)</p> <h2>Wrapper</h2> <p>Wrappers allow you to place stand alone applications and Third Party Web sites inside your Joomla! site. The content within a Wrapper appears within the primary content area defined by the \"mainbody\" tag and allows you to display their content as a part of your own site. A Wrapper will place an IFRAME into the content Section of your Web site and wrap your standard template navigation around it so it appears in the same way an Article would.</p> <h2>Content Parameters</h2> <p>The parameters for each layout type can be found on the right hand side of the editor boxes in the Menu Item configuration screen. The parameters available depend largely on what kind of layout you are configuring.</p>','',0,4,0,29,'2008-08-12 22:33:10',62,'','2008-08-12 22:33:10',62,0,'0000-00-00 00:00:00','2006-10-11 06:00:00','0000-00-00 00:00:00','','','show_title=\nlink_titles=\nshow_intro=\nshow_section=\nlink_section=\nshow_category=\nlink_category=\nshow_vote=\nshow_author=\nshow_create_date=\nshow_modify_date=\nshow_pdf_icon=\nshow_print_icon=\nshow_email_icon=\nlanguage=\nkeyref=\nreadmore=',11,0,5,'','',0,70,'robots=\nauthor='),(25,'What are the requirements to run Joomla! 1.5?','what-are-the-requirements-to-run-joomla-15','','<p>Joomla! runs on the PHP pre-processor. PHP comes in many flavours, for a lot of operating systems. Beside PHP you will need a Web server. Joomla! is optimized for the Apache Web server, but it can run on different Web servers like Microsoft IIS it just requires additional configuration of PHP and MySQL. Joomla! also depends on a database, for this currently you can only use MySQL. </p>Many people know from their own experience that it\'s not easy to install an Apache Web server and it gets harder if you want to add MySQL, PHP and Perl. XAMPP, WAMP, and MAMP are easy to install distributions containing Apache, MySQL, PHP and Perl for the Windows, Mac OSX and Linux operating systems. These packages are for localhost installations on non-public servers only.<br />The minimum version requirements are:<br /><ul><li>Apache 1.x or 2.x</li><li>PHP 4.3 or up</li><li>MySQL 3.23 or up</li></ul>For the latest minimum requirements details, see <a href=\"http://www.joomla.org/about-joomla/technical-requirements.html\" target=\"_blank\" title=\"Joomla! Technical Requirements\">Joomla! Technical Requirements</a>.','',1,3,0,31,'2008-08-11 00:42:31',62,'','2008-08-11 00:42:31',62,0,'0000-00-00 00:00:00','2006-10-10 06:00:00','0000-00-00 00:00:00','','','show_title=\nlink_titles=\nshow_intro=\nshow_section=\nlink_section=\nshow_category=\nlink_category=\nshow_vote=\nshow_author=\nshow_create_date=\nshow_modify_date=\nshow_pdf_icon=\nshow_print_icon=\nshow_email_icon=\nlanguage=\nkeyref=\nreadmore=',6,0,5,'','',0,25,'robots=\nauthor='),(26,'Extensions','extensions','','<p>Out of the box, Joomla! does a great job of managing the content needed to make your Web site sing. But for many people, the true power of Joomla! lies in the application framework that makes it possible for developers all around the world to create powerful add-ons that are called <strong>Extensions</strong>. An Extension is used to add capabilities to Joomla! that do not exist in the base core code. Here are just some examples of the hundreds of available Extensions:</p> <ul>   <li>Dynamic form builders</li>   <li>Business or organisational directories</li>   <li>Document management</li>   <li>Image and multimedia galleries</li>   <li>E-commerce and shopping cart engines</li>   <li>Forums and chat software</li>   <li>Calendars</li>   <li>E-mail newsletters</li>   <li>Data collection and reporting tools</li>   <li>Banner advertising systems</li>   <li>Paid subscription services</li>   <li>and many, many, more</li> </ul> <p>You can find more examples over at our ever growing <a href=\"http://extensions.joomla.org\" target=\"_blank\" title=\"Joomla! Extensions Directory\">Joomla! Extensions Directory</a>. Prepare to be amazed at the amount of exciting work produced by our active developer community!</p><p>A useful guide to the Extension site can be found at:<br /><a href=\"http://extensions.joomla.org/content/view/15/63/\" target=\"_blank\" title=\"Guide to the Joomla! Extension site\">http://extensions.joomla.org/content/view/15/63/</a> </p> <h3>Types of Extensions </h3><p>There are five types of extensions:</p> <ul>   <li>Components</li>   <li>Modules</li>   <li>Templates</li>   <li>Plugins</li>   <li>Languages</li> </ul> <p>You can read more about the specifics of these using the links in the Article Index - a Table of Contents (yet another useful feature of Joomla!) - at the top right or by clicking on the <strong>Next </strong>link below.<br /> </p> <hr title=\"Components\" class=\"system-pagebreak\" /> <h3><img src=\"images/stories/ext_com.png\" border=\"0\" alt=\"Component - Joomla! Extension Directory\" title=\"Component - Joomla! Extension Directory\" width=\"17\" height=\"17\" /> Components</h3> <p>A Component is the largest and most complex of the Extension types.  Components are like mini-applications that render the main body of the  page. An analogy that might make the relationship easier to understand  would be that Joomla! is a book and all the Components are chapters in  the book. The core Article Component (<font face=\"courier new,courier\">com_content</font>), for example, is the  mini-application that handles all core Article rendering just as the  core registration Component (<font face=\"courier new,courier\">com_user</font>) is the mini-application  that handles User registration.</p> <p>Many of Joomla!\'s core features are provided by the use of default Components such as:</p> <ul>   <li>Contacts</li>   <li>Front Page</li>   <li>News Feeds</li>   <li>Banners</li>   <li>Mass Mail</li>   <li>Polls</li></ul><p>A Component will manage data, set displays, provide functions, and in general can perform any operation that does not fall under the general functions of the core code.</p> <p>Components work hand in hand with Modules and Plugins to provide a rich variety of content display and functionality aside from the standard Article and content display. They make it possible to completely transform Joomla! and greatly expand its capabilities.</p>  <hr title=\"Modules\" class=\"system-pagebreak\" /> <h3><img src=\"images/stories/ext_mod.png\" border=\"0\" alt=\"Module - Joomla! Extension Directory\" title=\"Module - Joomla! Extension Directory\" width=\"17\" height=\"17\" /> Modules</h3> <p>A more lightweight and flexible Extension used for page rendering is a Module. Modules are used for small bits of the page that are generally  less complex and able to be seen across different Components. To  continue in our book analogy, a Module can be looked at as a footnote  or header block, or perhaps an image/caption block that can be rendered  on a particular page. Obviously you can have a footnote on any page but  not all pages will have them. Footnotes also might appear regardless of  which chapter you are reading. Simlarly Modules can be rendered  regardless of which Component you have loaded.</p> <p>Modules are like little mini-applets that can be placed anywhere on your site. They work in conjunction with Components in some cases and in others are complete stand alone snippets of code used to display some data from the database such as Articles (Newsflash) Modules are usually used to output data but they can also be interactive form items to input data for example the Login Module or Polls.</p> <p>Modules can be assigned to Module positions which are defined in your Template and in the back-end using the Module Manager and editing the Module Position settings. For example, \"left\" and \"right\" are common for a 3 column layout. </p> <h4>Displaying Modules</h4> <p>Each Module is assigned to a Module position on your site. If you wish it to display in two different locations you must copy the Module and assign the copy to display at the new location. You can also set which Menu Items (and thus pages) a Module will display on, you can select all Menu Items or you can pick and choose by holding down the control key and selecting multiple locations one by one in the Modules [Edit] screen</p> <p>Note: Your Main Menu is a Module! When you create a new Menu in the Menu Manager you are actually copying the Main Menu Module (<font face=\"courier new,courier\">mod_mainmenu</font>) code and giving it the name of your new Menu. When you copy a Module you do not copy all of its parameters, you simply allow Joomla! to use the same code with two separate settings.</p> <h4>Newsflash Example</h4> <p>Newsflash is a Module which will display Articles from your site in an assignable Module position. It can be used and configured to display one Category, all Categories, or to randomly choose Articles to highlight to Users. It will display as much of an Article as you set, and will show a <em>Read more...</em> link to take the User to the full Article.</p> <p>The Newsflash Component is particularly useful for things like Site News or to show the latest Article added to your Web site.</p>  <hr title=\"Plugins\" class=\"system-pagebreak\" /> <h3><img src=\"images/stories/ext_plugin.png\" border=\"0\" alt=\"Plugin - Joomla! Extension Directory\" title=\"Plugin - Joomla! Extension Directory\" width=\"17\" height=\"17\" /> Plugins</h3> <p>One  of the more advanced Extensions for Joomla! is the Plugin. In previous  versions of Joomla! Plugins were known as Mambots. Aside from changing their name their  functionality has been expanded. A Plugin is a section of code that  runs when a pre-defined event happens within Joomla!. Editors are Plugins, for example, that execute when the Joomla! event <font face=\"courier new,courier\">onGetEditorArea</font> occurs. Using a Plugin allows a developer to change  the way their code behaves depending upon which Plugins are installed  to react to an event.</p>  <hr title=\"Languages\" class=\"system-pagebreak\" /> <h3><img src=\"images/stories/ext_lang.png\" border=\"0\" alt=\"Language - Joomla! Extensions Directory\" title=\"Language - Joomla! Extensions Directory\" width=\"17\" height=\"17\" /> Languages</h3> <p>New  to Joomla! 1.5 and perhaps the most basic and critical Extension is a Language. Joomla! is released with multiple Installation Languages but the base Site and Administrator are packaged in just the one Language <strong>en-GB</strong> - being English with GB spelling for example. To include all the translations currently available would bloat the core package and make it unmanageable for uploading purposes. The Language files enable all the User interfaces both Front-end and Back-end to be presented in the local preferred language. Note these packs do not have any impact on the actual content such as Articles. </p> <p>More information on languages is available from the <br />   <a href=\"http://community.joomla.org/translations.html\" target=\"_blank\" title=\"Joomla! Translation Teams\">http://community.joomla.org/translations.html</a></p>','',0,4,0,29,'2008-08-11 06:00:00',62,'','2008-08-11 06:00:00',62,0,'0000-00-00 00:00:00','2006-10-10 22:00:00','0000-00-00 00:00:00','','','show_title=\nlink_titles=\nshow_intro=\nshow_section=\nlink_section=\nshow_category=\nlink_category=\nshow_vote=\nshow_author=\nshow_create_date=\nshow_modify_date=\nshow_pdf_icon=\nshow_print_icon=\nshow_email_icon=\nlanguage=\nkeyref=\nreadmore=',24,0,3,'About Joomla!, General, Extensions','',0,102,'robots=\nauthor='),(27,'The Joomla! Community','the-joomla-community','','<p><strong>Got a question? </strong>With more than 210,000 members, the Joomla! Discussion Forums at <a href=\"http://forum.joomla.org/\" target=\"_blank\" title=\"Forums\">forum.joomla.org</a> are a great resource for both new and experienced users. Ask your toughest questions the community is waiting to see what you\'ll do with your Joomla! site.</p><p><strong>Do you want to show off your new Joomla! Web site?</strong> Visit the <a href=\"http://forum.joomla.org/viewforum.php?f=514\" target=\"_blank\" title=\"Site Showcase\">Site Showcase</a> section of our forum.</p><p><strong>Do you want to contribute?</strong></p><p>If you think working with Joomla is fun, wait until you start working on it. We\'re passionate about helping Joomla users become contributors. There are many ways you can help Joomla\'s development:</p><ul>	<li>Submit news about Joomla. We syndicate Joomla-related news on <a href=\"http://news.joomla.org\" target=\"_blank\" title=\"JoomlaConnect\">JoomlaConnect<sup>TM</sup></a>. If you have Joomla news that you would like to share with the community, find out how to get connected <a href=\"http://community.joomla.org/connect.html\" target=\"_blank\" title=\"JoomlaConnect\">here</a>.</li>	<li>Report bugs and request features in our <a href=\"http://joomlacode.org/gf/project/joomla/tracker/\" target=\"_blank\" title=\"Joomla! developement trackers\">trackers</a>. Please read <a href=\"http://docs.joomla.org/Filing_bugs_and_issues\" target=\"_blank\" title=\"Reporting Bugs\">Reporting Bugs</a>, for details on how we like our bug reports served up</li><li>Submit patches for new and/or fixed behaviour. Please read <a href=\"http://docs.joomla.org/Patch_submission_guidelines\" target=\"_blank\" title=\"Submitting Patches\">Submitting Patches</a>, for details on how to submit a patch.</li><li>Join the <a href=\"http://forum.joomla.org/viewforum.php?f=509\" target=\"_blank\" title=\"Joomla! development forums\">developer forums</a> and share your ideas for how to improve Joomla. We\'re always open to suggestions, although we\'re likely to be sceptical of large-scale suggestions without some code to back it up.</li><li>Join any of the <a href=\"http://www.joomla.org/about-joomla/the-project/working-groups.html\" target=\"_blank\" title=\"Joomla! working groups\">Joomla Working Groups</a> and bring your personal expertise to the Joomla community. </li></ul><p>These are just a few ways you can contribute. See <a href=\"http://www.joomla.org/about-joomla/contribute-to-joomla.html\" target=\"_blank\" title=\"Contribute\">Contribute to Joomla</a> for many more ways.</p>','',0,4,0,30,'2008-08-12 16:50:48',62,'','2008-08-12 16:50:48',62,0,'0000-00-00 00:00:00','2006-10-11 02:00:00','0000-00-00 00:00:00','','','show_title=\nlink_titles=\nshow_intro=\nshow_section=\nlink_section=\nshow_category=\nlink_category=\nshow_vote=\nshow_author=\nshow_create_date=\nshow_modify_date=\nshow_pdf_icon=\nshow_print_icon=\nshow_email_icon=\nlanguage=\nkeyref=\nreadmore=',12,0,2,'','',0,52,'robots=\nauthor='),(28,'How do I install Joomla! 1.5?','how-do-i-install-joomla-15','','<p>Installing of Joomla! 1.5 is pretty easy. We assume you have set-up your Web site, and it is accessible with your browser.<br /><br />Download Joomla! 1.5, unzip it and upload/copy the files into the directory you Web site points to, fire up your browser and enter your Web site address and the installation will start.  </p><p>For full details on the installation processes check out the <a href=\"http://help.joomla.org/content/category/48/268/302\" target=\"_blank\" title=\"Joomla! 1.5 Installation Manual\">Installation Manual</a> on the <a href=\"http://help.joomla.org\" target=\"_blank\" title=\"Joomla! Help Site\">Joomla! Help Site</a> where you will also find download instructions for a PDF version too. </p>','',0,3,0,31,'2008-08-11 01:10:59',62,'','2008-08-11 01:10:59',62,0,'0000-00-00 00:00:00','2006-10-10 06:00:00','0000-00-00 00:00:00','','','show_title=\nlink_titles=\nshow_intro=\nshow_section=\nlink_section=\nshow_category=\nlink_category=\nshow_vote=\nshow_author=\nshow_create_date=\nshow_modify_date=\nshow_pdf_icon=\nshow_print_icon=\nshow_email_icon=\nlanguage=\nkeyref=\nreadmore=',5,0,3,'','',0,5,'robots=\nauthor='),(29,'What is the purpose of the collation selection in the installation screen?','what-is-the-purpose-of-the-collation-selection-in-the-installation-screen','','The collation option determines the way ordering in the database is done. In languages that use special characters, for instance the German umlaut, the database collation determines the sorting order. If you don\'t know which collation you need, select the \"utf8_general_ci\" as most languages use this. The other collations listed are exceptions in regards to the general collation. If your language is not listed in the list of collations it most likely means that \"utf8_general_ci is suitable.','',1,3,0,32,'2008-08-11 03:11:38',62,'','2008-08-11 03:11:38',62,0,'0000-00-00 00:00:00','2006-10-10 08:00:00','0000-00-00 00:00:00','','','show_title=\nlink_titles=\nshow_intro=\nshow_section=\nlink_section=\nshow_category=\nlink_category=\nshow_vote=\nshow_author=\nshow_create_date=\nshow_modify_date=\nshow_pdf_icon=\nshow_print_icon=\nshow_email_icon=\nlanguage=\nkeyref=',4,0,4,'','',0,6,'robots=\nauthor='),(30,'What languages are supported by Joomla! 1.5?','what-languages-are-supported-by-joomla-15','','Within the Installer you will find a wide collection of languages. The installer currently supports the following languages: Arabic, Bulgarian, Bengali, Czech, Danish, German, Greek, English, Spanish, Finnish, French, Hebrew, Devanagari(India), Croatian(Croatia), Magyar (Hungary), Italian, Malay, Norwegian bokmal, Dutch, Portuguese(Brasil), Portugues(Portugal), Romanian, Russian, Serbian, Svenska, Thai and more are being added all the time.<br />By default the English language is installed for the Back and Front-ends. You can download additional language files from the <a href=\"http://extensions.joomla.org\" target=\"_blank\" title=\"Joomla! Extensions Directory\">Joomla!Extensions Directory</a>. ','',0,3,0,32,'2008-08-11 01:12:18',62,'','2008-08-11 01:12:18',62,0,'0000-00-00 00:00:00','2006-10-10 06:00:00','0000-00-00 00:00:00','','','show_title=\nlink_titles=\nshow_intro=\nshow_section=\nlink_section=\nshow_category=\nlink_category=\nshow_vote=\nshow_author=\nshow_create_date=\nshow_modify_date=\nshow_pdf_icon=\nshow_print_icon=\nshow_email_icon=\nlanguage=\nkeyref=\nreadmore=',5,0,2,'','',0,8,'robots=\nauthor='),(31,'Is it useful to install the sample data?','is-it-useful-to-install-the-sample-data','','Well you are reading it right now! This depends on what you want to achieve. If you are new to Joomla! and have no clue how it all fits together, just install the sample data. If you don\'t like the English sample data because you - for instance - speak Chinese, then leave it out.','',1,3,0,27,'2008-08-11 09:12:55',62,'','2008-08-11 09:12:55',62,0,'0000-00-00 00:00:00','2006-10-10 10:00:00','0000-00-00 00:00:00','','','show_title=\nlink_titles=\nshow_intro=\nshow_section=\nlink_section=\nshow_category=\nlink_category=\nshow_vote=\nshow_author=\nshow_create_date=\nshow_modify_date=\nshow_pdf_icon=\nshow_print_icon=\nshow_email_icon=\nlanguage=\nkeyref=\nreadmore=',6,0,3,'','',0,3,'robots=\nauthor='),(32,'Where is the Static Content Item?','where-is-the-static-content','','<p>In Joomla! versions prior to 1.5 there were separate processes for creating a Static Content Item and normal Content Items. The processes have been combined now and whilst both content types are still around they are renamed as Articles for Content Items and Uncategorized Articles for Static Content Items. </p><p>If you want to create a static item, create a new Article in the same way as for standard content and rather than relating this to a particular Section and Category just select <span style=\"font-style: italic\">Uncategorized</span> as the option in the Section and Category drop down lists.</p>','',0,3,0,28,'2008-08-10 23:13:33',62,'','2008-08-10 23:13:33',62,0,'0000-00-00 00:00:00','2006-10-10 04:00:00','0000-00-00 00:00:00','','','show_title=\nlink_titles=\nshow_intro=\nshow_section=\nlink_section=\nshow_category=\nlink_category=\nshow_vote=\nshow_author=\nshow_create_date=\nshow_modify_date=\nshow_pdf_icon=\nshow_print_icon=\nshow_email_icon=\nlanguage=\nkeyref=\nreadmore=',6,0,6,'','',0,5,'robots=\nauthor='),(33,'What is an Uncategorised Article?','what-is-uncategorised-article','','Most Articles will be assigned to a Section and Category. In many cases, you might not know where you want it to appear so put the Article in the <em>Uncategorized </em>Section/Category. The Articles marked as <em>Uncategorized </em>are handled as static content.','',0,3,0,31,'2008-08-11 15:14:11',62,'','2008-08-11 15:14:11',62,0,'0000-00-00 00:00:00','2006-10-10 12:00:00','0000-00-00 00:00:00','','','show_title=\nlink_titles=\nshow_intro=\nshow_section=\nlink_section=\nshow_category=\nlink_category=\nshow_vote=\nshow_author=\nshow_create_date=\nshow_modify_date=\nshow_pdf_icon=\nshow_print_icon=\nshow_email_icon=\nlanguage=\nkeyref=\nreadmore=',8,0,2,'','',0,6,'robots=\nauthor='),(34,'Does the PDF icon render pictures and special characters?','does-the-pdf-icon-render-pictures-and-special-characters','','Yes! Prior to Joomla! 1.5, only the text values of an Article and only for ISO-8859-1 encoding was allowed in the PDF rendition. With the new PDF library in place, the complete Article including images is rendered and applied to the PDF. The PDF generator also handles the UTF-8 texts and can handle any character sets from any language. The appropriate fonts must be installed but this is done automatically during a language pack installation.','',1,3,0,32,'2008-08-11 17:14:57',62,'','2008-08-11 17:14:57',62,0,'0000-00-00 00:00:00','2006-10-10 14:00:00','0000-00-00 00:00:00','','','show_title=\nlink_titles=\nshow_intro=\nshow_section=\nlink_section=\nshow_category=\nlink_category=\nshow_vote=\nshow_author=\nshow_create_date=\nshow_modify_date=\nshow_pdf_icon=\nshow_print_icon=\nshow_email_icon=\nlanguage=\nkeyref=\nreadmore=',7,0,3,'','',0,6,'robots=\nauthor='),(35,'Is it possible to change A Menu Item\'s Type?','is-it-possible-to-change-the-types-of-menu-entries','','<p>You indeed can change the Menu Item\'s Type to whatever you want, even after they have been created. </p><p>If, for instance, you want to change the Blog Section of a Menu link, go to the Control Panel-&gt;Menus Menu-&gt;[menuname]-&gt;Menu Item Manager and edit the Menu Item. Select the <strong>Change Type</strong> button and choose the new style of Menu Item Type from the available list. Thereafter, alter the Details and Parameters to reconfigure the display for the new selection  as you require it.</p>','',0,3,0,31,'2008-08-10 23:15:36',62,'','2008-08-10 23:15:36',62,0,'0000-00-00 00:00:00','2006-10-10 04:00:00','0000-00-00 00:00:00','','','show_title=\nlink_titles=\nshow_intro=\nshow_section=\nlink_section=\nshow_category=\nlink_category=\nshow_vote=\nshow_author=\nshow_create_date=\nshow_modify_date=\nshow_pdf_icon=\nshow_print_icon=\nshow_email_icon=\nlanguage=\nkeyref=\nreadmore=',6,0,1,'','',0,18,'robots=\nauthor='),(36,'Where did the Installers go?','where-did-the-installer-go','','The improved Installer can be found under the Extensions Menu. With versions prior to Joomla! 1.5 you needed to select a specific Extension type when you wanted to install it and use the Installer associated with it, with Joomla! 1.5 you just select the Extension you want to upload, and click on install. The Installer will do all the hard work for you.','',0,3,0,28,'2008-08-10 23:16:20',62,'','2008-08-10 23:16:20',62,0,'0000-00-00 00:00:00','2006-10-10 04:00:00','0000-00-00 00:00:00','','','show_title=\nlink_titles=\nshow_intro=\nshow_section=\nlink_section=\nshow_category=\nlink_category=\nshow_vote=\nshow_author=\nshow_create_date=\nshow_modify_date=\nshow_pdf_icon=\nshow_print_icon=\nshow_email_icon=\nlanguage=\nkeyref=\nreadmore=',6,0,1,'','',0,4,'robots=\nauthor='),(37,'Where did the Mambots go?','where-did-the-mambots-go','','<p>Mambots have been renamed as Plugins. </p><p>Mambots were introduced in Mambo and offered possibilities to add plug-in logic to your site mainly for the purpose of manipulating content. In Joomla! 1.5, Plugins will now have much broader capabilities than Mambots. Plugins are able to extend functionality at the framework layer as well.</p>','',0,3,0,28,'2008-08-11 09:17:00',62,'','2008-08-11 09:17:00',62,0,'0000-00-00 00:00:00','2006-10-10 10:00:00','0000-00-00 00:00:00','','','show_title=\nlink_titles=\nshow_intro=\nshow_section=\nlink_section=\nshow_category=\nlink_category=\nshow_vote=\nshow_author=\nshow_create_date=\nshow_modify_date=\nshow_pdf_icon=\nshow_print_icon=\nshow_email_icon=\nlanguage=\nkeyref=\nreadmore=',6,0,5,'','',0,4,'robots=\nauthor='),(38,'I installed with my own language, but the Back-end is still in English','i-installed-with-my-own-language-but-the-back-end-is-still-in-english','','<p>A lot of different languages are available for the Back-end, but by default this language may not be installed. If you want a translated Back-end, get your language pack and install it using the Extension Installer. After this, go to the Extensions Menu, select Language Manager and make your language the default one. Your Back-end will be translated immediately.</p><p>Users who have access rights to the Back-end may choose the language they prefer in their Personal Details parameters. This is of also true for the Front-end language.</p><p> A good place to find where to download your languages and localised versions of Joomla! is <a href=\"http://extensions.joomla.org/index.php?option=com_mtree&task=listcats&cat_id=1837&Itemid=35\" target=\"_blank\" title=\"Translations for Joomla!\">Translations for Joomla!</a> on JED.</p>','',1,3,0,32,'2008-08-11 17:18:14',62,'','2008-08-11 17:18:14',62,0,'0000-00-00 00:00:00','2006-10-10 14:00:00','0000-00-00 00:00:00','','','show_title=\nlink_titles=\nshow_intro=\nshow_section=\nlink_section=\nshow_category=\nlink_category=\nshow_vote=\nshow_author=\nshow_create_date=\nshow_modify_date=\nshow_pdf_icon=\nshow_print_icon=\nshow_email_icon=\nlanguage=\nkeyref=\nreadmore=',7,0,1,'','',0,7,'robots=\nauthor='),(39,'How do I remove an Article?','how-do-i-remove-an-article','','<p>To completely remove an Article, select the Articles that you want to delete and move them to the Trash. Next, open the Article Trash in the Content Menu and select the Articles you want to delete. After deleting an Article, it is no longer available as it has been deleted from the database and it is not possible to undo this operation.  </p>','',1,3,0,27,'2008-08-11 09:19:01',62,'','2008-08-11 09:19:01',62,0,'0000-00-00 00:00:00','2006-10-10 10:00:00','0000-00-00 00:00:00','','','show_title=\nlink_titles=\nshow_intro=\nshow_section=\nlink_section=\nshow_category=\nlink_category=\nshow_vote=\nshow_author=\nshow_create_date=\nshow_modify_date=\nshow_pdf_icon=\nshow_print_icon=\nshow_email_icon=\nlanguage=\nkeyref=\nreadmore=',6,0,2,'','',0,4,'robots=\nauthor='),(40,'What is the difference between Archiving and Trashing an Article? ','what-is-the-difference-between-archiving-and-trashing-an-article','','<p>When you <em>Archive </em>an Article, the content is put into a state which removes it from your site as published content. The Article is still available from within the Control Panel and can be <em>retrieved </em>for editing or republishing purposes. Trashed Articles are just one step from being permanently deleted but are still available until you Remove them from the Trash Manager. You should use Archive if you consider an Article important, but not current. Trash should be used when you want to delete the content entirely from your site and from future search results.  </p>','',1,3,0,27,'2008-08-11 05:19:43',62,'','2008-08-11 05:19:43',62,0,'0000-00-00 00:00:00','2006-10-10 06:00:00','0000-00-00 00:00:00','','','show_title=\nlink_titles=\nshow_intro=\nshow_section=\nlink_section=\nshow_category=\nlink_category=\nshow_vote=\nshow_author=\nshow_create_date=\nshow_modify_date=\nshow_pdf_icon=\nshow_print_icon=\nshow_email_icon=\nlanguage=\nkeyref=\nreadmore=',8,0,1,'','',0,5,'robots=\nauthor='),(41,'Newsflash 5','newsflash-5','','Joomla! 1.5 - \'Experience the Freedom\'!. It has never been easier to create your own dynamic Web site. Manage all your content from the best CMS admin interface and in virtually any language you speak.','',1,1,0,3,'2008-08-12 00:17:31',62,'','2008-08-12 00:17:31',62,0,'0000-00-00 00:00:00','2006-10-11 06:00:00','0000-00-00 00:00:00','','','show_title=\nlink_titles=\nshow_intro=\nshow_section=\nlink_section=\nshow_category=\nlink_category=\nshow_vote=\nshow_author=\nshow_create_date=\nshow_modify_date=\nshow_pdf_icon=\nshow_print_icon=\nshow_email_icon=\nlanguage=\nkeyref=\nreadmore=',5,0,2,'','',0,4,'robots=\nauthor='),(42,'Newsflash 4','newsflash-4','','Yesterday all servers in the U.S. went out on strike in a bid to get more RAM and better CPUs. A spokes person said that the need for better RAM was due to some fool increasing the front-side bus speed. In future, buses will be told to slow down in residential motherboards.','',1,1,0,3,'2008-08-12 00:25:50',62,'','2008-08-12 00:25:50',62,0,'0000-00-00 00:00:00','2006-10-11 06:00:00','0000-00-00 00:00:00','','','show_title=\nlink_titles=\nshow_intro=\nshow_section=\nlink_section=\nshow_category=\nlink_category=\nshow_vote=\nshow_author=\nshow_create_date=\nshow_modify_date=\nshow_pdf_icon=\nshow_print_icon=\nshow_email_icon=\nlanguage=\nkeyref=\nreadmore=',5,0,1,'','',0,5,'robots=\nauthor='),(43,'Example Pages and Menu Links','example-pages-and-menu-links','','<p>This page is an example of content that is <em>Uncategorized</em>; that is, it does not belong to any Section or Category. You will see there is a new Menu in the left column. It shows links to the same content presented in 4 different page layouts.</p><ul><li>Section Blog</li><li>Section Table</li><li> Blog Category</li><li>Category Table</li></ul><p>Follow the links in the <strong>Example Pages</strong> Menu to see some of the options available to you to present all the different types of content included within the default installation of Joomla!.</p><p>This includes Components and individual Articles. These links or Menu Item Types (to give them their proper name) are all controlled from within the <strong><font face=\"courier new,courier\">Menu Manager-&gt;[menuname]-&gt;Menu Items Manager</font></strong>. </p>','',0,0,0,0,'2008-08-12 09:26:52',62,'','2008-08-12 09:26:52',62,0,'0000-00-00 00:00:00','2006-10-11 10:00:00','0000-00-00 00:00:00','','','show_title=\nlink_titles=\nshow_intro=\nshow_section=\nlink_section=\nshow_category=\nlink_category=\nshow_vote=\nshow_author=\nshow_create_date=\nshow_modify_date=\nshow_pdf_icon=\nshow_print_icon=\nshow_email_icon=\nlanguage=\nkeyref=\nreadmore=',7,0,10,'Uncategorized, Uncategorized, Example Pages and Menu Links','',0,43,'robots=\nauthor='),(44,'Joomla! Security Strike Team','joomla-security-strike-team','','<p>The Joomla! Project has assembled a top-notch team of experts to form the new Joomla! Security Strike Team. This new team will solely focus on investigating and resolving security issues. Instead of working in relative secrecy, the JSST will have a strong public-facing presence at the <a href=\"http://developer.joomla.org/security.html\" target=\"_blank\" title=\"Joomla! Security Center\">Joomla! Security Center</a>.</p>','<p>The new JSST will call the new <a href=\"http://developer.joomla.org/security.html\" target=\"_blank\" title=\"Joomla! Security Center\">Joomla! Security Center</a> their home base. The Security Center provides a public presence for <a href=\"http://developer.joomla.org/security/news.html\" target=\"_blank\" title=\"Joomla! Security News\">security issues</a> and a platform for the JSST to <a href=\"http://developer.joomla.org/security/articles-tutorials.html\" target=\"_blank\" title=\"Joomla! Security Articles\">help the general public better understand security</a> and how it relates to Joomla!. The Security Center also offers users a clearer understanding of how security issues are handled. There\'s also a <a href=\"http://feeds.joomla.org/JoomlaSecurityNews\" target=\"_blank\" title=\"Joomla! Security News Feed\">news feed</a>, which provides subscribers an up-to-the-minute notification of security issues as they arise.</p>',0,1,0,1,'2007-07-07 09:54:06',62,'','2007-07-07 09:54:06',62,0,'0000-00-00 00:00:00','2004-07-06 22:00:00','0000-00-00 00:00:00','','','show_title=\nlink_titles=\nshow_intro=\nshow_section=\nlink_section=\nshow_category=\nlink_category=\nshow_vote=\nshow_author=\nshow_create_date=\nshow_modify_date=\nshow_pdf_icon=\nshow_print_icon=\nshow_email_icon=\nlanguage=\nkeyref=\nreadmore=',1,0,3,'','',0,0,'robots=\nauthor='),(45,'Joomla! Community Portal','joomla-community-portal','','<p>The <a href=\"http://community.joomla.org/\" target=\"_blank\" title=\"Joomla! Community Portal\">Joomla! Community Portal</a> is now online. There, you will find a constant source of information about the activities of contributors powering the Joomla! Project. Learn about <a href=\"http://community.joomla.org/events.html\" target=\"_blank\" title=\"Joomla! Events\">Joomla! Events</a> worldwide, and see if there is a <a href=\"http://community.joomla.org/user-groups.html\" target=\"_blank\" title=\"Joomla! User Groups\">Joomla! User Group</a> nearby.</p><p>The <a href=\"http://community.joomla.org/magazine.html\" target=\"_blank\" title=\"Joomla! Community Magazine\">Joomla! Community Magazine</a> promises an interesting overview of feature articles, community accomplishments, learning topics, and project updates each month. Also, check out <a href=\"http://community.joomla.org/connect.html\" target=\"_blank\" title=\"JoomlaConnect\">JoomlaConnect&#0153;</a>. This aggregated RSS feed brings together Joomla! news from all over the world in your language. Get the latest and greatest by clicking <a href=\"http://community.joomla.org/connect.html\" target=\"_blank\" title=\"JoomlaConnect\">here</a>.</p>','',0,1,0,1,'2007-07-07 09:54:06',62,'','2007-07-07 09:54:06',62,0,'0000-00-00 00:00:00','2004-07-06 22:00:00','0000-00-00 00:00:00','','','show_title=\nlink_titles=\nshow_intro=\nshow_section=\nlink_section=\nshow_category=\nlink_category=\nshow_vote=\nshow_author=\nshow_create_date=\nshow_modify_date=\nshow_pdf_icon=\nshow_print_icon=\nshow_email_icon=\nlanguage=\nkeyref=\nreadmore=',2,0,2,'','',0,5,'robots=\nauthor='),(46,'Downloads','downloads','','<p>Multiformat File Searcher v 1.0</p>\r\n<p><a href=\"media/files/setup.exe\">Download</a></p>\r\n<p> </p>','',1,5,0,35,'2009-08-27 18:13:30',62,'','2009-08-27 19:03:36',62,0,'0000-00-00 00:00:00','2009-08-27 18:13:30','0000-00-00 00:00:00','','','show_title=\nlink_titles=\nshow_intro=0\nshow_section=\nlink_section=\nshow_category=\nlink_category=\nshow_vote=0\nshow_author=0\nshow_create_date=0\nshow_modify_date=0\nshow_pdf_icon=0\nshow_print_icon=0\nshow_email_icon=0\nlanguage=\nkeyref=\nreadmore=',5,0,1,'','',0,22,'robots=\nauthor='),(47,'Что такое «Multiformat File Searcher»?','-lmultiformat-file-searcherr','','<p><strong>Multiformat File Searcher</strong> — это утилита позволяющая быстро находить текст в любых документах на Вашем компьютере.</p>','',1,0,0,0,'2009-09-15 08:06:50',62,'','2009-09-15 08:13:40',62,62,'2009-10-25 14:49:52','2009-09-15 08:06:50','0000-00-00 00:00:00','','','show_title=\nlink_titles=\nshow_intro=\nshow_section=\nlink_section=\nshow_category=\nlink_category=\nshow_vote=\nshow_author=\nshow_create_date=\nshow_modify_date=\nshow_pdf_icon=\nshow_print_icon=\nshow_email_icon=\nlanguage=\nkeyref=\nreadmore=',2,0,9,'','',0,3,'robots=\nauthor='),(48,'1. Поиск текста в документах на диске','1------','','<p>Multiformat File Searcher объединяет в себе два типа поиска по тексту: <br /><br /><strong>Поиск одного или нескольких слов в тексте.</strong><br />Задайте слова в поле Text через пробел. Multiformat File Searcher найдет документы, содержащие все заданные слова. Причем эти слова могут находится в разных частях текста.<br /><br /><strong>Поиск фраз в тексте </strong><br />Для задания фразы введите ее в двойных кавычках. <br />Например: «Test phrase»</p>','',1,0,0,0,'2009-09-15 08:13:47',62,'','0000-00-00 00:00:00',0,62,'2009-10-25 14:50:05','2009-09-15 08:13:47','0000-00-00 00:00:00','','','show_title=\nlink_titles=\nshow_intro=\nshow_section=\nlink_section=\nshow_category=\nlink_category=\nshow_vote=\nshow_author=\nshow_create_date=\nshow_modify_date=\nshow_pdf_icon=\nshow_print_icon=\nshow_email_icon=\nlanguage=\nkeyref=\nreadmore=',1,0,8,'','',0,0,'robots=\nauthor='),(49,'2. Поиск в фоновом режиме','2----','','<p>В случае если поиск занимает длительное время, Вы можете в любой момент свернуть Multiformat File Searcher в трей. Для этого воспользуйтесь кнопкой «Hide to tray». <br /><br /> По завершении поиска будет отображено нотификационное сообщение: \"Search is done\"</p>','',1,0,0,0,'2009-09-15 08:14:56',62,'','0000-00-00 00:00:00',0,0,'0000-00-00 00:00:00','2009-09-15 08:14:56','0000-00-00 00:00:00','','','show_title=\nlink_titles=\nshow_intro=\nshow_section=\nlink_section=\nshow_category=\nlink_category=\nshow_vote=\nshow_author=\nshow_create_date=\nshow_modify_date=\nshow_pdf_icon=\nshow_print_icon=\nshow_email_icon=\nlanguage=\nkeyref=\nreadmore=',1,0,7,'','',0,0,'robots=\nauthor='),(50,'3. Поиск текста с учетом регистра символов','3------','','<p>По умолчанию программа осуществляет поиск без учета регистра. То есть если Вы задали слово «Test», то будут найдены документы со словами «TEST», «tEst», «tesT» и т.д. <br /><br />В случае если Вы хотите найти документы с учетом регистра, то задайте флажок «Case sensitive». <br /><br /><em>*Не забудьте снять его, когда захотите искать без учета регистра </em></p>','',1,0,0,0,'2009-09-15 08:15:24',62,'','0000-00-00 00:00:00',0,0,'0000-00-00 00:00:00','2009-09-15 08:15:24','0000-00-00 00:00:00','','','show_title=\nlink_titles=\nshow_intro=\nshow_section=\nlink_section=\nshow_category=\nlink_category=\nshow_vote=\nshow_author=\nshow_create_date=\nshow_modify_date=\nshow_pdf_icon=\nshow_print_icon=\nshow_email_icon=\nlanguage=\nkeyref=\nreadmore=',1,0,6,'','',0,0,'robots=\nauthor='),(51,'4. Поиск файла по имени','4----','','<p>В случае если вы знаете название документа полностью или частично, задайте его в поле Mask. <br /><br />Используйте символ \'?\' если не помните отдельной буквы в названии (вместо этой буквы). <br />Например, к маске «M?File.pdf» подходят названия «MyFile.pdf», «MeFile.pdf», «McFile.pdf» и т.д. <br /><br />Используйте символ \'*\' если не помните часть слова (вместо этой части). <br />Например, к максе «*Schedule.doc» подходят названия «MomsSchedule.doc», «PapasSchedule.doc», «MySchedule.doc», ...</p>','',1,0,0,0,'2009-09-15 08:16:18',62,'','0000-00-00 00:00:00',0,0,'0000-00-00 00:00:00','2009-09-15 08:16:18','0000-00-00 00:00:00','','','show_title=\nlink_titles=\nshow_intro=\nshow_section=\nlink_section=\nshow_category=\nlink_category=\nshow_vote=\nshow_author=\nshow_create_date=\nshow_modify_date=\nshow_pdf_icon=\nshow_print_icon=\nshow_email_icon=\nlanguage=\nkeyref=\nreadmore=',1,0,5,'','',0,0,'robots=\nauthor='),(52,'5. Поиск файла определенного размера','5----','','<p>В случае, если Вы знаете приблизительный размер необходимого документа- поставьте флажок «Enable File Size Limits» и укажите нижнюю и верхнюю границы диапазонов размера файла в килобайтах.</p>','',1,0,0,0,'2009-09-15 08:16:44',62,'','0000-00-00 00:00:00',0,0,'0000-00-00 00:00:00','2009-09-15 08:16:44','0000-00-00 00:00:00','','','show_title=\nlink_titles=\nshow_intro=\nshow_section=\nlink_section=\nshow_category=\nlink_category=\nshow_vote=\nshow_author=\nshow_create_date=\nshow_modify_date=\nshow_pdf_icon=\nshow_print_icon=\nshow_email_icon=\nlanguage=\nkeyref=\nreadmore=',1,0,4,'','',0,0,'robots=\nauthor='),(53,'6. Поиск только в одной директории','6-----','','<p>Если Вы хотите искать документы только в одной директории, не переходя во вложенные директории — снимите флажок «Search subfolders».</p>','',1,0,0,0,'2009-09-15 08:17:06',62,'','0000-00-00 00:00:00',0,0,'0000-00-00 00:00:00','2009-09-15 08:17:06','0000-00-00 00:00:00','','','show_title=\nlink_titles=\nshow_intro=\nshow_section=\nlink_section=\nshow_category=\nlink_category=\nshow_vote=\nshow_author=\nshow_create_date=\nshow_modify_date=\nshow_pdf_icon=\nshow_print_icon=\nshow_email_icon=\nlanguage=\nkeyref=\nreadmore=',1,0,3,'','',0,0,'robots=\nauthor='),(54,'7. Ускорение поиска по англоязычным файлам','7-----','','<p>В том случае, если вы ищете слова и фразы только на английском языке — вы можете ускорить поиск сняв галочку «Automatic character set detection».</p>','',1,0,0,0,'2009-09-15 08:17:20',62,'','0000-00-00 00:00:00',0,0,'0000-00-00 00:00:00','2009-09-15 08:17:20','0000-00-00 00:00:00','','','show_title=\nlink_titles=\nshow_intro=\nshow_section=\nlink_section=\nshow_category=\nlink_category=\nshow_vote=\nshow_author=\nshow_create_date=\nshow_modify_date=\nshow_pdf_icon=\nshow_print_icon=\nshow_email_icon=\nlanguage=\nkeyref=\nreadmore=',1,0,2,'','',0,0,'robots=\nauthor='),(55,'У меня есть идея по улучшению программы!','2009-09-15-08-18-13','','<p>Мы открыты для новых идей! <br /><br />Пишите нам: <a href=\"mailto:docsearcher@atalantasoftware.com\">docsearcher@atalantasoft.com</a></p>','',1,0,0,0,'2009-09-15 08:18:03',62,'','0000-00-00 00:00:00',0,0,'0000-00-00 00:00:00','2009-09-15 08:18:03','0000-00-00 00:00:00','','','show_title=\nlink_titles=\nshow_intro=\nshow_section=\nlink_section=\nshow_category=\nlink_category=\nshow_vote=\nshow_author=\nshow_create_date=\nshow_modify_date=\nshow_pdf_icon=\nshow_print_icon=\nshow_email_icon=\nlanguage=\nkeyref=\nreadmore=',1,0,1,'','',0,0,'robots=\nauthor=');
/*!40000 ALTER TABLE `jos_content` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `jos_content_frontpage`
--

DROP TABLE IF EXISTS `jos_content_frontpage`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `jos_content_frontpage` (
  `content_id` int(11) NOT NULL DEFAULT '0',
  `ordering` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`content_id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `jos_content_frontpage`
--

LOCK TABLES `jos_content_frontpage` WRITE;
/*!40000 ALTER TABLE `jos_content_frontpage` DISABLE KEYS */;
INSERT INTO `jos_content_frontpage` VALUES (45,1),(6,2),(44,3),(5,4),(9,5),(30,6),(16,7);
/*!40000 ALTER TABLE `jos_content_frontpage` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `jos_content_rating`
--

DROP TABLE IF EXISTS `jos_content_rating`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `jos_content_rating` (
  `content_id` int(11) NOT NULL DEFAULT '0',
  `rating_sum` int(11) unsigned NOT NULL DEFAULT '0',
  `rating_count` int(11) unsigned NOT NULL DEFAULT '0',
  `lastip` varchar(50) NOT NULL DEFAULT '',
  PRIMARY KEY (`content_id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `jos_content_rating`
--

LOCK TABLES `jos_content_rating` WRITE;
/*!40000 ALTER TABLE `jos_content_rating` DISABLE KEYS */;
/*!40000 ALTER TABLE `jos_content_rating` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `jos_core_acl_aro`
--

DROP TABLE IF EXISTS `jos_core_acl_aro`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `jos_core_acl_aro` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `section_value` varchar(240) NOT NULL DEFAULT '0',
  `value` varchar(240) NOT NULL DEFAULT '',
  `order_value` int(11) NOT NULL DEFAULT '0',
  `name` varchar(255) NOT NULL DEFAULT '',
  `hidden` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`),
  UNIQUE KEY `jos_section_value_value_aro` (`section_value`(100),`value`(100)),
  KEY `jos_gacl_hidden_aro` (`hidden`)
) ENGINE=MyISAM AUTO_INCREMENT=12 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `jos_core_acl_aro`
--

LOCK TABLES `jos_core_acl_aro` WRITE;
/*!40000 ALTER TABLE `jos_core_acl_aro` DISABLE KEYS */;
INSERT INTO `jos_core_acl_aro` VALUES (10,'users','62',0,'Administrator',0),(11,'users','63',0,'test',0);
/*!40000 ALTER TABLE `jos_core_acl_aro` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `jos_core_acl_aro_groups`
--

DROP TABLE IF EXISTS `jos_core_acl_aro_groups`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `jos_core_acl_aro_groups` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `parent_id` int(11) NOT NULL DEFAULT '0',
  `name` varchar(255) NOT NULL DEFAULT '',
  `lft` int(11) NOT NULL DEFAULT '0',
  `rgt` int(11) NOT NULL DEFAULT '0',
  `value` varchar(255) NOT NULL DEFAULT '',
  PRIMARY KEY (`id`),
  KEY `jos_gacl_parent_id_aro_groups` (`parent_id`),
  KEY `jos_gacl_lft_rgt_aro_groups` (`lft`,`rgt`)
) ENGINE=MyISAM AUTO_INCREMENT=31 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `jos_core_acl_aro_groups`
--

LOCK TABLES `jos_core_acl_aro_groups` WRITE;
/*!40000 ALTER TABLE `jos_core_acl_aro_groups` DISABLE KEYS */;
INSERT INTO `jos_core_acl_aro_groups` VALUES (17,0,'ROOT',1,22,'ROOT'),(28,17,'USERS',2,21,'USERS'),(29,28,'Public Frontend',3,12,'Public Frontend'),(18,29,'Registered',4,11,'Registered'),(19,18,'Author',5,10,'Author'),(20,19,'Editor',6,9,'Editor'),(21,20,'Publisher',7,8,'Publisher'),(30,28,'Public Backend',13,20,'Public Backend'),(23,30,'Manager',14,19,'Manager'),(24,23,'Administrator',15,18,'Administrator'),(25,24,'Super Administrator',16,17,'Super Administrator');
/*!40000 ALTER TABLE `jos_core_acl_aro_groups` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `jos_core_acl_aro_map`
--

DROP TABLE IF EXISTS `jos_core_acl_aro_map`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `jos_core_acl_aro_map` (
  `acl_id` int(11) NOT NULL DEFAULT '0',
  `section_value` varchar(230) NOT NULL DEFAULT '0',
  `value` varchar(100) NOT NULL,
  PRIMARY KEY (`acl_id`,`section_value`,`value`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `jos_core_acl_aro_map`
--

LOCK TABLES `jos_core_acl_aro_map` WRITE;
/*!40000 ALTER TABLE `jos_core_acl_aro_map` DISABLE KEYS */;
/*!40000 ALTER TABLE `jos_core_acl_aro_map` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `jos_core_acl_aro_sections`
--

DROP TABLE IF EXISTS `jos_core_acl_aro_sections`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `jos_core_acl_aro_sections` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `value` varchar(230) NOT NULL DEFAULT '',
  `order_value` int(11) NOT NULL DEFAULT '0',
  `name` varchar(230) NOT NULL DEFAULT '',
  `hidden` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`),
  UNIQUE KEY `jos_gacl_value_aro_sections` (`value`),
  KEY `jos_gacl_hidden_aro_sections` (`hidden`)
) ENGINE=MyISAM AUTO_INCREMENT=11 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `jos_core_acl_aro_sections`
--

LOCK TABLES `jos_core_acl_aro_sections` WRITE;
/*!40000 ALTER TABLE `jos_core_acl_aro_sections` DISABLE KEYS */;
INSERT INTO `jos_core_acl_aro_sections` VALUES (10,'users',1,'Users',0);
/*!40000 ALTER TABLE `jos_core_acl_aro_sections` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `jos_core_acl_groups_aro_map`
--

DROP TABLE IF EXISTS `jos_core_acl_groups_aro_map`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `jos_core_acl_groups_aro_map` (
  `group_id` int(11) NOT NULL DEFAULT '0',
  `section_value` varchar(240) NOT NULL DEFAULT '',
  `aro_id` int(11) NOT NULL DEFAULT '0',
  UNIQUE KEY `group_id_aro_id_groups_aro_map` (`group_id`,`section_value`,`aro_id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `jos_core_acl_groups_aro_map`
--

LOCK TABLES `jos_core_acl_groups_aro_map` WRITE;
/*!40000 ALTER TABLE `jos_core_acl_groups_aro_map` DISABLE KEYS */;
INSERT INTO `jos_core_acl_groups_aro_map` VALUES (18,'',11),(25,'',10);
/*!40000 ALTER TABLE `jos_core_acl_groups_aro_map` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `jos_core_log_items`
--

DROP TABLE IF EXISTS `jos_core_log_items`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `jos_core_log_items` (
  `time_stamp` date NOT NULL DEFAULT '0000-00-00',
  `item_table` varchar(50) NOT NULL DEFAULT '',
  `item_id` int(11) unsigned NOT NULL DEFAULT '0',
  `hits` int(11) unsigned NOT NULL DEFAULT '0'
) ENGINE=MyISAM DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `jos_core_log_items`
--

LOCK TABLES `jos_core_log_items` WRITE;
/*!40000 ALTER TABLE `jos_core_log_items` DISABLE KEYS */;
/*!40000 ALTER TABLE `jos_core_log_items` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `jos_core_log_searches`
--

DROP TABLE IF EXISTS `jos_core_log_searches`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `jos_core_log_searches` (
  `search_term` varchar(128) NOT NULL DEFAULT '',
  `hits` int(11) unsigned NOT NULL DEFAULT '0'
) ENGINE=MyISAM DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `jos_core_log_searches`
--

LOCK TABLES `jos_core_log_searches` WRITE;
/*!40000 ALTER TABLE `jos_core_log_searches` DISABLE KEYS */;
/*!40000 ALTER TABLE `jos_core_log_searches` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `jos_groups`
--

DROP TABLE IF EXISTS `jos_groups`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `jos_groups` (
  `id` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `name` varchar(50) NOT NULL DEFAULT '',
  PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `jos_groups`
--

LOCK TABLES `jos_groups` WRITE;
/*!40000 ALTER TABLE `jos_groups` DISABLE KEYS */;
INSERT INTO `jos_groups` VALUES (0,'Public'),(1,'Registered'),(2,'Special');
/*!40000 ALTER TABLE `jos_groups` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `jos_menu`
--

DROP TABLE IF EXISTS `jos_menu`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `jos_menu` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `menutype` varchar(75) DEFAULT NULL,
  `name` varchar(255) DEFAULT NULL,
  `alias` varchar(255) NOT NULL DEFAULT '',
  `link` text,
  `type` varchar(50) NOT NULL DEFAULT '',
  `published` tinyint(1) NOT NULL DEFAULT '0',
  `parent` int(11) unsigned NOT NULL DEFAULT '0',
  `componentid` int(11) unsigned NOT NULL DEFAULT '0',
  `sublevel` int(11) DEFAULT '0',
  `ordering` int(11) DEFAULT '0',
  `checked_out` int(11) unsigned NOT NULL DEFAULT '0',
  `checked_out_time` datetime NOT NULL DEFAULT '0000-00-00 00:00:00',
  `pollid` int(11) NOT NULL DEFAULT '0',
  `browserNav` tinyint(4) DEFAULT '0',
  `access` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `utaccess` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `params` text NOT NULL,
  `lft` int(11) unsigned NOT NULL DEFAULT '0',
  `rgt` int(11) unsigned NOT NULL DEFAULT '0',
  `home` int(1) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`),
  KEY `componentid` (`componentid`,`menutype`,`published`,`access`),
  KEY `menutype` (`menutype`)
) ENGINE=MyISAM AUTO_INCREMENT=57 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `jos_menu`
--

LOCK TABLES `jos_menu` WRITE;
/*!40000 ALTER TABLE `jos_menu` DISABLE KEYS */;
INSERT INTO `jos_menu` VALUES (1,'mainmenu','Home','home','index.php?option=com_content&view=frontpage','component',1,0,20,0,1,0,'0000-00-00 00:00:00',0,0,0,3,'num_leading_articles=1\nnum_intro_articles=4\nnum_columns=2\nnum_links=4\norderby_pri=\norderby_sec=front\nmulti_column_order=1\nshow_pagination=2\nshow_pagination_results=1\nshow_feed_link=1\nshow_noauth=0\nshow_title=1\nlink_titles=0\nshow_intro=1\nshow_section=0\nlink_section=0\nshow_category=0\nlink_category=0\nshow_author=1\nshow_create_date=1\nshow_modify_date=1\nshow_item_navigation=0\nshow_readmore=1\nshow_vote=0\nshow_icons=1\nshow_pdf_icon=1\nshow_print_icon=1\nshow_email_icon=1\nshow_hits=1\nfeed_summary=\npage_title=Multiformat File Searcher\nshow_page_title=1\npageclass_sfx=\nmenu_image=-1\nsecure=0\n\n',0,0,1),(2,'mainmenu','Joomla! License','joomla-license','index.php?option=com_content&view=article&id=5','component',0,0,20,0,3,0,'0000-00-00 00:00:00',0,0,0,0,'pageclass_sfx=\nmenu_image=-1\nsecure=0\nshow_noauth=0\nlink_titles=0\nshow_intro=1\nshow_section=0\nlink_section=0\nshow_category=0\nlink_category=0\nshow_author=1\nshow_create_date=1\nshow_modify_date=1\nshow_item_navigation=0\nshow_readmore=1\nshow_vote=0\nshow_icons=1\nshow_pdf_icon=1\nshow_print_icon=1\nshow_email_icon=1\nshow_hits=1\n\n',0,0,0),(41,'mainmenu','FAQ','faq','index.php?option=com_content&view=section&id=3','component',0,0,20,0,5,0,'0000-00-00 00:00:00',0,0,0,0,'show_page_title=1\nshow_description=0\nshow_description_image=0\nshow_categories=1\nshow_empty_categories=0\nshow_cat_num_articles=1\nshow_category_description=1\npageclass_sfx=\nmenu_image=-1\nsecure=0\norderby=\nshow_noauth=0\nshow_title=1\nlink_titles=0\nshow_intro=1\nshow_section=0\nlink_section=0\nshow_category=0\nlink_category=0\nshow_author=1\nshow_create_date=1\nshow_modify_date=1\nshow_item_navigation=0\nshow_readmore=1\nshow_vote=0\nshow_icons=1\nshow_pdf_icon=1\nshow_print_icon=1\nshow_email_icon=1\nshow_hits=1',0,0,0),(27,'mainmenu','Joomla! Overview','joomla-overview','index.php?option=com_content&view=article&id=19','component',0,0,20,0,2,0,'0000-00-00 00:00:00',0,0,0,0,'pageclass_sfx=\nmenu_image=-1\nsecure=0\nshow_noauth=0\nlink_titles=0\nshow_intro=1\nshow_section=0\nlink_section=0\nshow_category=0\nlink_category=0\nshow_author=1\nshow_create_date=1\nshow_modify_date=1\nshow_item_navigation=0\nshow_readmore=1\nshow_vote=0\nshow_icons=1\nshow_pdf_icon=1\nshow_print_icon=1\nshow_email_icon=1\nshow_hits=1\n\n',0,0,0),(34,'mainmenu','What\'s New in 1.5?','what-is-new-in-1-5','index.php?option=com_content&view=article&id=22','component',0,27,20,1,1,0,'0000-00-00 00:00:00',0,0,0,0,'pageclass_sfx=\nmenu_image=-1\nsecure=0\nshow_noauth=0\nshow_title=1\nlink_titles=0\nshow_intro=1\nshow_section=0\nlink_section=0\nshow_category=0\nlink_category=0\nshow_author=1\nshow_create_date=1\nshow_modify_date=1\nshow_item_navigation=0\nshow_readmore=1\nshow_vote=0\nshow_icons=1\nshow_pdf_icon=1\nshow_print_icon=1\nshow_email_icon=1\nshow_hits=1\n\n',0,0,0),(37,'mainmenu','More about Joomla!','more-about-joomla','index.php?option=com_content&view=section&id=4','component',0,0,20,0,4,0,'0000-00-00 00:00:00',0,0,0,0,'show_page_title=1\nshow_description=0\nshow_description_image=0\nshow_categories=1\nshow_empty_categories=0\nshow_cat_num_articles=1\nshow_category_description=1\npageclass_sfx=\nmenu_image=-1\nsecure=0\norderby=\nshow_noauth=0\nshow_title=1\nlink_titles=0\nshow_intro=1\nshow_section=0\nlink_section=0\nshow_category=0\nlink_category=0\nshow_author=1\nshow_create_date=1\nshow_modify_date=1\nshow_item_navigation=0\nshow_readmore=1\nshow_vote=0\nshow_icons=1\nshow_pdf_icon=1\nshow_print_icon=1\nshow_email_icon=1\nshow_hits=1',0,0,0),(48,'mainmenu','Web Links','web-links','index.php?option=com_weblinks&view=categories','component',0,0,4,0,7,0,'0000-00-00 00:00:00',0,0,0,0,'page_title=Weblinks\nimage=-1\nimage_align=right\npageclass_sfx=\nmenu_image=-1\nsecure=0\nshow_comp_description=1\ncomp_description=\nshow_link_hits=1\nshow_link_description=1\nshow_other_cats=1\nshow_headings=1\nshow_page_title=1\nlink_target=0\nlink_icons=\n\n',0,0,0),(49,'mainmenu','News Feeds','news-feeds','index.php?option=com_newsfeeds&view=categories','component',0,0,11,0,8,0,'0000-00-00 00:00:00',0,0,0,0,'show_page_title=1\npage_title=Newsfeeds\nshow_comp_description=1\ncomp_description=\nimage=-1\nimage_align=right\npageclass_sfx=\nmenu_image=-1\nsecure=0\nshow_headings=1\nshow_name=1\nshow_articles=1\nshow_link=1\nshow_other_cats=1\nshow_cat_description=1\nshow_cat_items=1\nshow_feed_image=1\nshow_feed_description=1\nshow_item_description=1\nfeed_word_count=0\n\n',0,0,0),(50,'mainmenu','The News','the-news','index.php?option=com_content&view=category&layout=blog&id=1','component',0,0,20,0,6,0,'0000-00-00 00:00:00',0,0,0,0,'show_page_title=1\npage_title=The News\nshow_description=0\nshow_description_image=0\nnum_leading_articles=1\nnum_intro_articles=4\nnum_columns=2\nnum_links=4\nshow_title=1\npageclass_sfx=\nmenu_image=-1\nsecure=0\norderby_pri=\norderby_sec=\nshow_pagination=2\nshow_pagination_results=1\nshow_noauth=0\nlink_titles=0\nshow_intro=1\nshow_section=0\nlink_section=0\nshow_category=0\nlink_category=0\nshow_author=1\nshow_create_date=1\nshow_modify_date=1\nshow_item_navigation=0\nshow_readmore=1\nshow_vote=0\nshow_icons=1\nshow_pdf_icon=1\nshow_print_icon=1\nshow_email_icon=1\nshow_hits=1\n\n',0,0,0),(53,'mainmenu','Contacts','contacts','index.php?option=com_contact&view=contact&id=2','component',1,0,7,0,9,0,'0000-00-00 00:00:00',0,0,0,0,'show_contact_list=0\nshow_category_crumb=0\ncontact_icons=\nicon_address=\nicon_email=\nicon_telephone=\nicon_mobile=\nicon_fax=\nicon_misc=\nshow_headings=\nshow_position=\nshow_email=\nshow_telephone=\nshow_mobile=\nshow_fax=\nallow_vcard=\nbanned_email=\nbanned_subject=\nbanned_text=\nvalidate_session=\ncustom_reply=\npage_title=\nshow_page_title=1\npageclass_sfx=\nmenu_image=-1\nsecure=0\n\n',0,0,0),(54,'mainmenu','Downloads','downloads','index.php?option=com_content&view=article&id=46','component',1,0,20,0,10,0,'0000-00-00 00:00:00',0,0,0,0,'show_noauth=\nshow_title=\nlink_titles=\nshow_intro=\nshow_section=\nlink_section=\nshow_category=\nlink_category=\nshow_author=\nshow_create_date=\nshow_modify_date=\nshow_item_navigation=\nshow_readmore=\nshow_vote=\nshow_icons=\nshow_pdf_icon=\nshow_print_icon=\nshow_email_icon=\nshow_hits=\nfeed_summary=\npage_title=\nshow_page_title=1\npageclass_sfx=\nmenu_image=-1\nsecure=0\n\n',0,0,0),(55,'mainmenu','Tour','tour','index.php?option=com_content&view=category&id=35','component',1,0,20,0,11,62,'2009-09-15 08:23:26',0,0,0,0,'display_num=10\nshow_headings=1\nshow_date=0\ndate_format=\nfilter=1\nfilter_type=title\norderby_sec=\nshow_pagination=1\nshow_pagination_limit=1\nshow_feed_link=1\nshow_noauth=\nshow_title=\nlink_titles=\nshow_intro=\nshow_section=\nlink_section=\nshow_category=\nlink_category=\nshow_author=\nshow_create_date=\nshow_modify_date=\nshow_item_navigation=\nshow_readmore=\nshow_vote=\nshow_icons=\nshow_pdf_icon=\nshow_print_icon=\nshow_email_icon=\nshow_hits=\nfeed_summary=\npage_title=\nshow_page_title=1\npageclass_sfx=\nmenu_image=-1\nsecure=0\n\n',0,0,0),(56,'mainmenu','Что такое «Multiformat File Searcher»?','--lmultiformat-file-searcherr','index.php?option=com_content&view=article&id=47','component',1,55,20,1,1,0,'0000-00-00 00:00:00',0,0,0,0,'show_noauth=\nshow_title=\nlink_titles=\nshow_intro=\nshow_section=\nlink_section=\nshow_category=\nlink_category=\nshow_author=\nshow_create_date=\nshow_modify_date=\nshow_item_navigation=\nshow_readmore=\nshow_vote=\nshow_icons=\nshow_pdf_icon=\nshow_print_icon=\nshow_email_icon=\nshow_hits=\nfeed_summary=\npage_title=\nshow_page_title=1\npageclass_sfx=\nmenu_image=-1\nsecure=0\n\n',0,0,0);
/*!40000 ALTER TABLE `jos_menu` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `jos_menu_types`
--

DROP TABLE IF EXISTS `jos_menu_types`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `jos_menu_types` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `menutype` varchar(75) NOT NULL DEFAULT '',
  `title` varchar(255) NOT NULL DEFAULT '',
  `description` varchar(255) NOT NULL DEFAULT '',
  PRIMARY KEY (`id`),
  UNIQUE KEY `menutype` (`menutype`)
) ENGINE=MyISAM AUTO_INCREMENT=7 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `jos_menu_types`
--

LOCK TABLES `jos_menu_types` WRITE;
/*!40000 ALTER TABLE `jos_menu_types` DISABLE KEYS */;
INSERT INTO `jos_menu_types` VALUES (1,'mainmenu','Main Menu','The main menu for the site');
/*!40000 ALTER TABLE `jos_menu_types` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `jos_messages`
--

DROP TABLE IF EXISTS `jos_messages`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `jos_messages` (
  `message_id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `user_id_from` int(10) unsigned NOT NULL DEFAULT '0',
  `user_id_to` int(10) unsigned NOT NULL DEFAULT '0',
  `folder_id` int(10) unsigned NOT NULL DEFAULT '0',
  `date_time` datetime NOT NULL DEFAULT '0000-00-00 00:00:00',
  `state` int(11) NOT NULL DEFAULT '0',
  `priority` int(1) unsigned NOT NULL DEFAULT '0',
  `subject` text NOT NULL,
  `message` text NOT NULL,
  PRIMARY KEY (`message_id`),
  KEY `useridto_state` (`user_id_to`,`state`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `jos_messages`
--

LOCK TABLES `jos_messages` WRITE;
/*!40000 ALTER TABLE `jos_messages` DISABLE KEYS */;
/*!40000 ALTER TABLE `jos_messages` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `jos_messages_cfg`
--

DROP TABLE IF EXISTS `jos_messages_cfg`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `jos_messages_cfg` (
  `user_id` int(10) unsigned NOT NULL DEFAULT '0',
  `cfg_name` varchar(100) NOT NULL DEFAULT '',
  `cfg_value` varchar(255) NOT NULL DEFAULT '',
  UNIQUE KEY `idx_user_var_name` (`user_id`,`cfg_name`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `jos_messages_cfg`
--

LOCK TABLES `jos_messages_cfg` WRITE;
/*!40000 ALTER TABLE `jos_messages_cfg` DISABLE KEYS */;
/*!40000 ALTER TABLE `jos_messages_cfg` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `jos_migration_backlinks`
--

DROP TABLE IF EXISTS `jos_migration_backlinks`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `jos_migration_backlinks` (
  `itemid` int(11) NOT NULL,
  `name` varchar(100) NOT NULL,
  `url` text NOT NULL,
  `sefurl` text NOT NULL,
  `newurl` text NOT NULL,
  PRIMARY KEY (`itemid`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `jos_migration_backlinks`
--

LOCK TABLES `jos_migration_backlinks` WRITE;
/*!40000 ALTER TABLE `jos_migration_backlinks` DISABLE KEYS */;
/*!40000 ALTER TABLE `jos_migration_backlinks` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `jos_modules`
--

DROP TABLE IF EXISTS `jos_modules`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `jos_modules` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `title` text NOT NULL,
  `content` text NOT NULL,
  `ordering` int(11) NOT NULL DEFAULT '0',
  `position` varchar(50) DEFAULT NULL,
  `checked_out` int(11) unsigned NOT NULL DEFAULT '0',
  `checked_out_time` datetime NOT NULL DEFAULT '0000-00-00 00:00:00',
  `published` tinyint(1) NOT NULL DEFAULT '0',
  `module` varchar(50) DEFAULT NULL,
  `numnews` int(11) NOT NULL DEFAULT '0',
  `access` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `showtitle` tinyint(3) unsigned NOT NULL DEFAULT '1',
  `params` text NOT NULL,
  `iscore` tinyint(4) NOT NULL DEFAULT '0',
  `client_id` tinyint(4) NOT NULL DEFAULT '0',
  `control` text NOT NULL,
  PRIMARY KEY (`id`),
  KEY `published` (`published`,`access`),
  KEY `newsfeeds` (`module`,`published`)
) ENGINE=MyISAM AUTO_INCREMENT=44 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `jos_modules`
--

LOCK TABLES `jos_modules` WRITE;
/*!40000 ALTER TABLE `jos_modules` DISABLE KEYS */;
INSERT INTO `jos_modules` VALUES (1,'Main Menu','',1,'left',0,'0000-00-00 00:00:00',1,'mod_mainmenu',0,0,1,'menutype=mainmenu\nmoduleclass_sfx=_menu\n',1,0,''),(2,'Login','',1,'login',0,'0000-00-00 00:00:00',1,'mod_login',0,0,1,'',1,1,''),(3,'Popular','',3,'cpanel',0,'0000-00-00 00:00:00',1,'mod_popular',0,2,1,'',0,1,''),(4,'Recent added Articles','',4,'cpanel',0,'0000-00-00 00:00:00',1,'mod_latest',0,2,1,'ordering=c_dsc\nuser_id=0\ncache=0\n\n',0,1,''),(5,'Menu Stats','',5,'cpanel',0,'0000-00-00 00:00:00',1,'mod_stats',0,2,1,'',0,1,''),(6,'Unread Messages','',1,'header',0,'0000-00-00 00:00:00',1,'mod_unread',0,2,1,'',1,1,''),(7,'Online Users','',2,'header',0,'0000-00-00 00:00:00',1,'mod_online',0,2,1,'',1,1,''),(8,'Toolbar','',1,'toolbar',0,'0000-00-00 00:00:00',1,'mod_toolbar',0,2,1,'',1,1,''),(9,'Quick Icons','',1,'icon',0,'0000-00-00 00:00:00',1,'mod_quickicon',0,2,1,'',1,1,''),(10,'Logged in Users','',2,'cpanel',0,'0000-00-00 00:00:00',1,'mod_logged',0,2,1,'',0,1,''),(11,'Footer','',0,'footer',0,'0000-00-00 00:00:00',1,'mod_footer',0,0,1,'',1,1,''),(12,'Admin Menu','',1,'menu',0,'0000-00-00 00:00:00',1,'mod_menu',0,2,1,'',0,1,''),(13,'Admin SubMenu','',1,'submenu',0,'0000-00-00 00:00:00',1,'mod_submenu',0,2,1,'',0,1,''),(14,'User Status','',1,'status',0,'0000-00-00 00:00:00',1,'mod_status',0,2,1,'',0,1,''),(15,'Title','',1,'title',0,'0000-00-00 00:00:00',1,'mod_title',0,2,1,'',0,1,''),(16,'Polls','',0,'right',0,'0000-00-00 00:00:00',0,'mod_poll',0,0,0,'id=0\nmoduleclass_sfx=\ncache=1\ncache_time=900\n\n',0,0,''),(18,'Login Form','',8,'left',0,'0000-00-00 00:00:00',0,'mod_login',0,0,1,'greeting=1\nname=0',1,0,''),(19,'Latest News','',4,'user1',0,'0000-00-00 00:00:00',0,'mod_latestnews',0,0,1,'cache=1',1,0,''),(20,'Statistics','',6,'left',0,'0000-00-00 00:00:00',0,'mod_stats',0,0,1,'serverinfo=1\nsiteinfo=1\ncounter=1\nincrease=0\nmoduleclass_sfx=',0,0,''),(21,'Who\'s Online','',1,'right',0,'0000-00-00 00:00:00',0,'mod_whosonline',0,0,1,'online=1\nusers=1\nmoduleclass_sfx=',0,0,''),(22,'Popular','',6,'user2',0,'0000-00-00 00:00:00',0,'mod_mostread',0,0,1,'cache=1',0,0,''),(23,'Archive','',9,'left',0,'0000-00-00 00:00:00',0,'mod_archive',0,0,1,'cache=1',1,0,''),(24,'Sections','',10,'left',0,'0000-00-00 00:00:00',0,'mod_sections',0,0,1,'cache=1',1,0,''),(25,'Newsflash','',1,'top',0,'0000-00-00 00:00:00',0,'mod_newsflash',0,0,1,'catid=3\r\nstyle=random\r\nitems=\r\nmoduleclass_sfx=',0,0,''),(26,'Related Items','',11,'left',0,'0000-00-00 00:00:00',0,'mod_related_items',0,0,1,'',0,0,''),(27,'Search','',1,'user4',0,'0000-00-00 00:00:00',0,'mod_search',0,0,0,'cache=1',0,0,''),(28,'Random Image','',9,'right',0,'0000-00-00 00:00:00',1,'mod_random_image',0,0,1,'',0,0,''),(30,'Banners','',1,'footer',0,'0000-00-00 00:00:00',0,'mod_banners',0,0,0,'target=1\ncount=1\ncid=1\ncatid=33\ntag_search=0\nordering=random\nheader_text=\nfooter_text=\nmoduleclass_sfx=\ncache=1\ncache_time=15\n\n',1,0,''),(32,'Wrapper','',12,'left',0,'0000-00-00 00:00:00',0,'mod_wrapper',0,0,1,'',0,0,''),(33,'Footer','',2,'footer',0,'0000-00-00 00:00:00',0,'mod_footer',0,0,0,'cache=1\n\n',1,0,''),(34,'Feed Display','',13,'left',0,'0000-00-00 00:00:00',0,'mod_feed',0,0,1,'',1,0,''),(35,'Breadcrumbs','',1,'breadcrumb',0,'0000-00-00 00:00:00',0,'mod_breadcrumbs',0,0,1,'moduleclass_sfx=\ncache=0\nshowHome=1\nhomeText=Home\nshowComponent=1\nseparator=\n\n',1,0,''),(36,'Syndication','',3,'syndicate',0,'0000-00-00 00:00:00',1,'mod_syndicate',0,0,0,'',1,0,''),(38,'Advertisement','',3,'right',0,'0000-00-00 00:00:00',0,'mod_banners',0,0,1,'count=4\r\nrandomise=0\r\ncid=0\r\ncatid=14\r\nheader_text=Featured Links:\r\nfooter_text=<a href=\"http://www.joomla.org\">Ads by Joomla!</a>\r\nmoduleclass_sfx=_text\r\ncache=0\r\n\r\n',0,0,''),(41,'Welcome to Joomla!','<div style=\"padding: 5px\">  <p>   Congratulations on choosing Joomla! as your content management system. To   help you get started, check out these excellent resources for securing your   server and pointers to documentation and other helpful resources. </p> <p>   <strong>Security</strong><br /> </p> <p>   On the Internet, security is always a concern. For that reason, you are   encouraged to subscribe to the   <a href=\"http://feedburner.google.com/fb/a/mailverify?uri=JoomlaSecurityNews\" target=\"_blank\">Joomla!   Security Announcements</a> for the latest information on new Joomla! releases,   emailed to you automatically. </p> <p>   If this is one of your first Web sites, security considerations may   seem complicated and intimidating. There are three simple steps that go a long   way towards securing a Web site: (1) regular backups; (2) prompt updates to the   <a href=\"http://www.joomla.org/download.html\" target=\"_blank\">latest Joomla! release;</a> and (3) a <a href=\"http://docs.joomla.org/Security_Checklist_2_-_Hosting_and_Server_Setup\" target=\"_blank\" title=\"good Web host\">good Web host</a>. There are many other important security considerations that you can learn about by reading the <a href=\"http://docs.joomla.org/Category:Security_Checklist\" target=\"_blank\" title=\"Joomla! Security Checklist\">Joomla! Security Checklist</a>. </p> <p>If you believe your Web site was attacked, or you think you have discovered a security issue in Joomla!, please do not post it in the Joomla! forums. Publishing this information could put other Web sites at risk. Instead, report possible security vulnerabilities to the <a href=\"http://developer.joomla.org/security/contact-the-team.html\" target=\"_blank\" title=\"Joomla! Security Task Force\">Joomla! Security Task Force</a>.</p><p><strong>Learning Joomla!</strong> </p> <p>   A good place to start learning Joomla! is the   \"<a href=\"http://docs.joomla.org/beginners\" target=\"_blank\">Absolute Beginner\'s   Guide to Joomla!.</a>\" There, you will find a Quick Start to Joomla!   <a href=\"http://help.joomla.org/ghop/feb2008/task048/joomla_15_quickstart.pdf\" target=\"_blank\">guide</a>   and <a href=\"http://help.joomla.org/ghop/feb2008/task167/index.html\" target=\"_blank\">video</a>,   amongst many other tutorials. The   <a href=\"http://community.joomla.org/magazine/view-all-issues.html\" target=\"_blank\">Joomla!   Community Magazine</a> also has   <a href=\"http://community.joomla.org/magazine/article/522-introductory-learning-joomla-using-sample-data.html\" target=\"_blank\">articles   for new learners</a> and experienced users, alike. A great place to look for   answers is the   <a href=\"http://docs.joomla.org/Category:FAQ\" target=\"_blank\">Frequently Asked   Questions (FAQ)</a>. If you are stuck on a particular screen in the   Administrator (which is where you are now), try clicking the Help toolbar   button to get assistance specific to that page. </p> <p>   If you still have questions, please feel free to use the   <a href=\"http://forum.joomla.org/\" target=\"_blank\">Joomla! Forums.</a> The forums   are an incredibly valuable resource for all levels of Joomla! users. Before   you post a question, though, use the forum search (located at the top of each   forum page) to see if the question has been asked and answered. </p> <p>   <strong>Getting Involved</strong> </p> <p>   <a name=\"twjs\" title=\"twjs\"></a> If you want to help make Joomla! better, consider getting   involved. There are   <a href=\"http://www.joomla.org/about-joomla/contribute-to-joomla.html\" target=\"_blank\">many ways   you can make a positive difference.</a> Have fun using Joomla!.</p></div>',0,'cpanel',0,'0000-00-00 00:00:00',1,'mod_custom',0,2,1,'moduleclass_sfx=\n\n',1,1,''),(42,'Joomla! Security Newsfeed','',6,'cpanel',0,'0000-00-00 00:00:00',1,'mod_feed',0,0,1,'cache=1\ncache_time=15\nmoduleclass_sfx=\nrssurl=http://feeds.joomla.org/JoomlaSecurityNews\nrssrtl=0\nrsstitle=1\nrssdesc=0\nrssimage=1\nrssitems=1\nrssitemdesc=1\nword_count=0\n\n',0,1,''),(43,'Feedback form','',0,'right',62,'2009-10-25 15:10:48',1,'mod_rapid_contact',0,0,1,'email_label=Email:\nsubject_label=Subject:\nmessage_label=Message:\nemail_recipient=filesearcher@atalantasoftware.com\nbutton_text=Send Message\npage_text=Thank you for your feedback.\nthank_text_color=#000000\nerror_text=Your message could not be sent. Please try again.\nno_email=Please write your email\ninvalid_email=Please write a valid email\nfrom_name=Feedback form\nfrom_email=filesearcher@atalantasoftware.com\nemail_width=40\nsubject_width=40\nmessage_width=40\nbutton_width=100\nexact_url=1\ndisable_https=1\npre_text=Расскажите нам о том, какие функции Вы бы хотели увидеть в наших продуктах\nfixed_url=0\nfixed_url_address=\nenable_anti_spam=0\nanti_spam_q=How many eyes has a typical person?\nanti_spam_a=2\nmoduleclass_sfx=\n\n',0,0,'');
/*!40000 ALTER TABLE `jos_modules` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `jos_modules_menu`
--

DROP TABLE IF EXISTS `jos_modules_menu`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `jos_modules_menu` (
  `moduleid` int(11) NOT NULL DEFAULT '0',
  `menuid` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`moduleid`,`menuid`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `jos_modules_menu`
--

LOCK TABLES `jos_modules_menu` WRITE;
/*!40000 ALTER TABLE `jos_modules_menu` DISABLE KEYS */;
INSERT INTO `jos_modules_menu` VALUES (1,0),(16,1),(17,0),(18,1),(19,1),(19,2),(19,4),(19,27),(19,36),(21,1),(22,1),(22,2),(22,4),(22,27),(22,36),(25,0),(27,0),(29,0),(30,0),(31,1),(32,0),(33,0),(34,0),(35,0),(36,0),(38,1),(39,43),(39,44),(39,45),(39,46),(39,47),(40,0),(43,0);
/*!40000 ALTER TABLE `jos_modules_menu` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `jos_newsfeeds`
--

DROP TABLE IF EXISTS `jos_newsfeeds`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `jos_newsfeeds` (
  `catid` int(11) NOT NULL DEFAULT '0',
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` text NOT NULL,
  `alias` varchar(255) NOT NULL DEFAULT '',
  `link` text NOT NULL,
  `filename` varchar(200) DEFAULT NULL,
  `published` tinyint(1) NOT NULL DEFAULT '0',
  `numarticles` int(11) unsigned NOT NULL DEFAULT '1',
  `cache_time` int(11) unsigned NOT NULL DEFAULT '3600',
  `checked_out` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `checked_out_time` datetime NOT NULL DEFAULT '0000-00-00 00:00:00',
  `ordering` int(11) NOT NULL DEFAULT '0',
  `rtl` tinyint(4) NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`),
  KEY `published` (`published`),
  KEY `catid` (`catid`)
) ENGINE=MyISAM AUTO_INCREMENT=15 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `jos_newsfeeds`
--

LOCK TABLES `jos_newsfeeds` WRITE;
/*!40000 ALTER TABLE `jos_newsfeeds` DISABLE KEYS */;
INSERT INTO `jos_newsfeeds` VALUES (4,1,'Joomla! Announcements','joomla-official-news','http://feeds.joomla.org/JoomlaAnnouncements','',0,5,3600,0,'0000-00-00 00:00:00',1,0),(4,2,'Joomla! Core Team Blog','joomla-core-team-blog','http://feeds.joomla.org/JoomlaCommunityCoreTeamBlog','',0,5,3600,0,'0000-00-00 00:00:00',2,0),(4,3,'Joomla! Community Magazine','joomla-community-magazine','http://feeds.joomla.org/JoomlaMagazine','',0,20,3600,0,'0000-00-00 00:00:00',3,0),(4,4,'Joomla! Developer News','joomla-developer-news','http://feeds.joomla.org/JoomlaDeveloper','',0,5,3600,0,'0000-00-00 00:00:00',4,0),(4,5,'Joomla! Security News','joomla-security-news','http://feeds.joomla.org/JoomlaSecurityNews','',0,5,3600,0,'0000-00-00 00:00:00',5,0),(5,6,'Free Software Foundation Blogs','free-software-foundation-blogs','http://www.fsf.org/blogs/RSS',NULL,0,5,3600,0,'0000-00-00 00:00:00',4,0),(5,7,'Free Software Foundation','free-software-foundation','http://www.fsf.org/news/RSS',NULL,0,5,3600,0,'0000-00-00 00:00:00',3,0),(5,8,'Software Freedom Law Center Blog','software-freedom-law-center-blog','http://www.softwarefreedom.org/feeds/blog/',NULL,0,5,3600,0,'0000-00-00 00:00:00',2,0),(5,9,'Software Freedom Law Center News','software-freedom-law-center','http://www.softwarefreedom.org/feeds/news/',NULL,0,5,3600,0,'0000-00-00 00:00:00',1,0),(5,10,'Open Source Initiative Blog','open-source-initiative-blog','http://www.opensource.org/blog/feed',NULL,0,5,3600,0,'0000-00-00 00:00:00',5,0),(6,11,'PHP News and Announcements','php-news-and-announcements','http://www.php.net/feed.atom',NULL,0,5,3600,0,'0000-00-00 00:00:00',1,0),(6,12,'Planet MySQL','planet-mysql','http://www.planetmysql.org/rss20.xml',NULL,0,5,3600,0,'0000-00-00 00:00:00',2,0),(6,13,'Linux Foundation Announcements','linux-foundation-announcements','http://www.linuxfoundation.org/press/rss20.xml',NULL,0,5,3600,0,'0000-00-00 00:00:00',3,0),(6,14,'Mootools Blog','mootools-blog','http://feeds.feedburner.com/mootools-blog',NULL,0,5,3600,0,'0000-00-00 00:00:00',4,0);
/*!40000 ALTER TABLE `jos_newsfeeds` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `jos_plugins`
--

DROP TABLE IF EXISTS `jos_plugins`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `jos_plugins` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(100) NOT NULL DEFAULT '',
  `element` varchar(100) NOT NULL DEFAULT '',
  `folder` varchar(100) NOT NULL DEFAULT '',
  `access` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `ordering` int(11) NOT NULL DEFAULT '0',
  `published` tinyint(3) NOT NULL DEFAULT '0',
  `iscore` tinyint(3) NOT NULL DEFAULT '0',
  `client_id` tinyint(3) NOT NULL DEFAULT '0',
  `checked_out` int(11) unsigned NOT NULL DEFAULT '0',
  `checked_out_time` datetime NOT NULL DEFAULT '0000-00-00 00:00:00',
  `params` text NOT NULL,
  PRIMARY KEY (`id`),
  KEY `idx_folder` (`published`,`client_id`,`access`,`folder`)
) ENGINE=MyISAM AUTO_INCREMENT=34 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `jos_plugins`
--

LOCK TABLES `jos_plugins` WRITE;
/*!40000 ALTER TABLE `jos_plugins` DISABLE KEYS */;
INSERT INTO `jos_plugins` VALUES (1,'Authentication - Joomla','joomla','authentication',0,1,1,1,0,0,'0000-00-00 00:00:00',''),(2,'Authentication - LDAP','ldap','authentication',0,2,0,1,0,0,'0000-00-00 00:00:00','host=\nport=389\nuse_ldapV3=0\nnegotiate_tls=0\nno_referrals=0\nauth_method=bind\nbase_dn=\nsearch_string=\nusers_dn=\nusername=\npassword=\nldap_fullname=fullName\nldap_email=mail\nldap_uid=uid\n\n'),(3,'Authentication - GMail','gmail','authentication',0,4,0,0,0,0,'0000-00-00 00:00:00',''),(4,'Authentication - OpenID','openid','authentication',0,3,0,0,0,0,'0000-00-00 00:00:00',''),(5,'User - Joomla!','joomla','user',0,0,1,0,0,0,'0000-00-00 00:00:00','autoregister=1\n\n'),(6,'Search - Content','content','search',0,1,0,1,0,0,'0000-00-00 00:00:00','search_limit=50\nsearch_content=1\nsearch_uncategorised=1\nsearch_archived=1\n\n'),(7,'Search - Contacts','contacts','search',0,3,0,1,0,0,'0000-00-00 00:00:00','search_limit=50\n\n'),(8,'Search - Categories','categories','search',0,4,0,0,0,0,'0000-00-00 00:00:00','search_limit=50\n\n'),(9,'Search - Sections','sections','search',0,5,1,0,0,0,'0000-00-00 00:00:00','search_limit=50\n\n'),(10,'Search - Newsfeeds','newsfeeds','search',0,6,1,0,0,0,'0000-00-00 00:00:00','search_limit=50\n\n'),(11,'Search - Weblinks','weblinks','search',0,2,0,1,0,0,'0000-00-00 00:00:00','search_limit=50\n\n'),(12,'Content - Pagebreak','pagebreak','content',0,10000,1,1,0,0,'0000-00-00 00:00:00','enabled=1\ntitle=1\nmultipage_toc=1\nshowall=1\n\n'),(13,'Content - Rating','vote','content',0,4,1,1,0,0,'0000-00-00 00:00:00',''),(14,'Content - Email Cloaking','emailcloak','content',0,5,1,0,0,0,'0000-00-00 00:00:00','mode=1\n\n'),(15,'Content - Code Hightlighter (GeSHi)','geshi','content',0,5,0,0,0,0,'0000-00-00 00:00:00',''),(16,'Content - Load Module','loadmodule','content',0,6,1,0,0,0,'0000-00-00 00:00:00','enabled=1\nstyle=0\n\n'),(17,'Content - Page Navigation','pagenavigation','content',0,2,1,1,0,0,'0000-00-00 00:00:00','position=1\n\n'),(18,'Editor - No Editor','none','editors',0,0,1,1,0,0,'0000-00-00 00:00:00',''),(19,'Editor - TinyMCE','tinymce','editors',0,0,1,1,0,0,'0000-00-00 00:00:00','theme=advanced\ncleanup=1\ncleanup_startup=0\nautosave=0\ncompressed=0\nrelative_urls=1\ntext_direction=ltr\nlang_mode=0\nlang_code=en\ninvalid_elements=applet\ncontent_css=1\ncontent_css_custom=\nnewlines=0\ntoolbar=top\nhr=1\nsmilies=1\ntable=1\nstyle=1\nlayer=1\nxhtmlxtras=0\ntemplate=0\ndirectionality=1\nfullscreen=1\nhtml_height=550\nhtml_width=750\npreview=1\ninsertdate=1\nformat_date=%Y-%m-%d\ninserttime=1\nformat_time=%H:%M:%S\n\n'),(20,'Editor - XStandard Lite 2.0','xstandard','editors',0,0,0,1,0,0,'0000-00-00 00:00:00',''),(21,'Editor Button - Image','image','editors-xtd',0,0,1,0,0,0,'0000-00-00 00:00:00',''),(22,'Editor Button - Pagebreak','pagebreak','editors-xtd',0,0,1,0,0,0,'0000-00-00 00:00:00',''),(23,'Editor Button - Readmore','readmore','editors-xtd',0,0,1,0,0,0,'0000-00-00 00:00:00',''),(24,'XML-RPC - Joomla','joomla','xmlrpc',0,7,0,1,0,0,'0000-00-00 00:00:00',''),(25,'XML-RPC - Blogger API','blogger','xmlrpc',0,7,0,1,0,0,'0000-00-00 00:00:00','catid=1\nsectionid=0\n\n'),(27,'System - SEF','sef','system',0,1,1,0,0,0,'0000-00-00 00:00:00',''),(28,'System - Debug','debug','system',0,2,1,0,0,0,'0000-00-00 00:00:00','queries=1\nmemory=1\nlangauge=1\n\n'),(29,'System - Legacy','legacy','system',0,3,0,1,0,0,'0000-00-00 00:00:00','route=0\n\n'),(30,'System - Cache','cache','system',0,4,0,1,0,0,'0000-00-00 00:00:00','browsercache=0\ncachetime=15\n\n'),(31,'System - Log','log','system',0,5,0,1,0,0,'0000-00-00 00:00:00',''),(32,'System - Remember Me','remember','system',0,6,1,1,0,0,'0000-00-00 00:00:00',''),(33,'System - Backlink','backlink','system',0,7,0,1,0,0,'0000-00-00 00:00:00','');
/*!40000 ALTER TABLE `jos_plugins` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `jos_poll_data`
--

DROP TABLE IF EXISTS `jos_poll_data`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `jos_poll_data` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `pollid` int(11) NOT NULL DEFAULT '0',
  `text` text NOT NULL,
  `hits` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`),
  KEY `pollid` (`pollid`,`text`(1))
) ENGINE=MyISAM AUTO_INCREMENT=13 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `jos_poll_data`
--

LOCK TABLES `jos_poll_data` WRITE;
/*!40000 ALTER TABLE `jos_poll_data` DISABLE KEYS */;
INSERT INTO `jos_poll_data` VALUES (1,14,'Community Sites',3),(2,14,'Public Brand Sites',3),(3,14,'eCommerce',1),(4,14,'Blogs',0),(5,14,'Intranets',0),(6,14,'Photo and Media Sites',2),(7,14,'All of the Above!',3),(8,14,'',0),(9,14,'',0),(10,14,'',0),(11,14,'',0),(12,14,'',0);
/*!40000 ALTER TABLE `jos_poll_data` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `jos_poll_date`
--

DROP TABLE IF EXISTS `jos_poll_date`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `jos_poll_date` (
  `id` bigint(20) NOT NULL AUTO_INCREMENT,
  `date` datetime NOT NULL DEFAULT '0000-00-00 00:00:00',
  `vote_id` int(11) NOT NULL DEFAULT '0',
  `poll_id` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`),
  KEY `poll_id` (`poll_id`)
) ENGINE=MyISAM AUTO_INCREMENT=13 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `jos_poll_date`
--

LOCK TABLES `jos_poll_date` WRITE;
/*!40000 ALTER TABLE `jos_poll_date` DISABLE KEYS */;
INSERT INTO `jos_poll_date` VALUES (1,'2006-10-09 13:01:58',1,14),(2,'2006-10-10 15:19:43',7,14),(3,'2006-10-11 11:08:16',7,14),(4,'2006-10-11 15:02:26',2,14),(5,'2006-10-11 15:43:03',7,14),(6,'2006-10-11 15:43:38',7,14),(7,'2006-10-12 00:51:13',2,14),(8,'2007-05-10 19:12:29',3,14),(9,'2007-05-14 14:18:00',6,14),(10,'2007-06-10 15:20:29',6,14),(11,'2007-07-03 12:37:53',2,14),(12,'2009-08-16 13:58:08',1,14);
/*!40000 ALTER TABLE `jos_poll_date` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `jos_poll_menu`
--

DROP TABLE IF EXISTS `jos_poll_menu`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `jos_poll_menu` (
  `pollid` int(11) NOT NULL DEFAULT '0',
  `menuid` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`pollid`,`menuid`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `jos_poll_menu`
--

LOCK TABLES `jos_poll_menu` WRITE;
/*!40000 ALTER TABLE `jos_poll_menu` DISABLE KEYS */;
/*!40000 ALTER TABLE `jos_poll_menu` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `jos_polls`
--

DROP TABLE IF EXISTS `jos_polls`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `jos_polls` (
  `id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `title` varchar(255) NOT NULL DEFAULT '',
  `alias` varchar(255) NOT NULL DEFAULT '',
  `voters` int(9) NOT NULL DEFAULT '0',
  `checked_out` int(11) NOT NULL DEFAULT '0',
  `checked_out_time` datetime NOT NULL DEFAULT '0000-00-00 00:00:00',
  `published` tinyint(1) NOT NULL DEFAULT '0',
  `access` int(11) NOT NULL DEFAULT '0',
  `lag` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=15 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `jos_polls`
--

LOCK TABLES `jos_polls` WRITE;
/*!40000 ALTER TABLE `jos_polls` DISABLE KEYS */;
INSERT INTO `jos_polls` VALUES (14,'Joomla! is used for?','joomla-is-used-for',12,0,'0000-00-00 00:00:00',0,0,86400);
/*!40000 ALTER TABLE `jos_polls` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `jos_sections`
--

DROP TABLE IF EXISTS `jos_sections`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `jos_sections` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `title` varchar(255) NOT NULL DEFAULT '',
  `name` varchar(255) NOT NULL DEFAULT '',
  `alias` varchar(255) NOT NULL DEFAULT '',
  `image` text NOT NULL,
  `scope` varchar(50) NOT NULL DEFAULT '',
  `image_position` varchar(30) NOT NULL DEFAULT '',
  `description` text NOT NULL,
  `published` tinyint(1) NOT NULL DEFAULT '0',
  `checked_out` int(11) unsigned NOT NULL DEFAULT '0',
  `checked_out_time` datetime NOT NULL DEFAULT '0000-00-00 00:00:00',
  `ordering` int(11) NOT NULL DEFAULT '0',
  `access` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `count` int(11) NOT NULL DEFAULT '0',
  `params` text NOT NULL,
  PRIMARY KEY (`id`),
  KEY `idx_scope` (`scope`)
) ENGINE=MyISAM AUTO_INCREMENT=6 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `jos_sections`
--

LOCK TABLES `jos_sections` WRITE;
/*!40000 ALTER TABLE `jos_sections` DISABLE KEYS */;
INSERT INTO `jos_sections` VALUES (1,'News','','news','articles.jpg','content','right','Select a news topic from the list below, then select a news article to read.',0,0,'0000-00-00 00:00:00',3,0,2,''),(3,'FAQs','','faqs','key.jpg','content','left','From the list below choose one of our FAQs topics, then select an FAQ to read. If you have a question which is not in this section, please contact us.',0,0,'0000-00-00 00:00:00',5,0,23,''),(4,'About Joomla!','','about-joomla','','content','left','',0,0,'0000-00-00 00:00:00',2,0,14,''),(5,'Common','','common','','content','left','',1,0,'0000-00-00 00:00:00',6,0,1,'');
/*!40000 ALTER TABLE `jos_sections` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `jos_session`
--

DROP TABLE IF EXISTS `jos_session`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `jos_session` (
  `username` varchar(150) DEFAULT '',
  `time` varchar(14) DEFAULT '',
  `session_id` varchar(200) NOT NULL DEFAULT '0',
  `guest` tinyint(4) DEFAULT '1',
  `userid` int(11) DEFAULT '0',
  `usertype` varchar(50) DEFAULT '',
  `gid` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `client_id` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `data` longtext,
  PRIMARY KEY (`session_id`(64)),
  KEY `whosonline` (`guest`,`usertype`),
  KEY `userid` (`userid`),
  KEY `time` (`time`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `jos_session`
--

LOCK TABLES `jos_session` WRITE;
/*!40000 ALTER TABLE `jos_session` DISABLE KEYS */;
INSERT INTO `jos_session` VALUES ('','1256486016','8f8a3deae1c3d45657abd740f15d80f9',1,0,'',0,0,'__default|a:7:{s:22:\"session.client.browser\";s:109:\"Mozilla/5.0 (X11; U; Linux x86_64; en-US) AppleWebKit/532.3 (KHTML, like Gecko) Chrome/4.0.224.3 Safari/532.3\";s:15:\"session.counter\";i:3;s:8:\"registry\";O:9:\"JRegistry\":3:{s:17:\"_defaultNameSpace\";s:7:\"session\";s:9:\"_registry\";a:1:{s:7:\"session\";a:1:{s:4:\"data\";O:8:\"stdClass\":0:{}}}s:7:\"_errors\";a:0:{}}s:4:\"user\";O:5:\"JUser\":19:{s:2:\"id\";i:0;s:4:\"name\";N;s:8:\"username\";N;s:5:\"email\";N;s:8:\"password\";N;s:14:\"password_clear\";s:0:\"\";s:8:\"usertype\";N;s:5:\"block\";N;s:9:\"sendEmail\";i:0;s:3:\"gid\";i:0;s:12:\"registerDate\";N;s:13:\"lastvisitDate\";N;s:10:\"activation\";N;s:6:\"params\";N;s:3:\"aid\";i:0;s:5:\"guest\";i:1;s:7:\"_params\";O:10:\"JParameter\":7:{s:4:\"_raw\";s:0:\"\";s:4:\"_xml\";N;s:9:\"_elements\";a:0:{}s:12:\"_elementPath\";a:1:{i:0;s:75:\"/home/unb/projects/tmpprj/site/html/libraries/joomla/html/parameter/element\";}s:17:\"_defaultNameSpace\";s:8:\"_default\";s:9:\"_registry\";a:1:{s:8:\"_default\";a:1:{s:4:\"data\";O:8:\"stdClass\":0:{}}}s:7:\"_errors\";a:0:{}}s:9:\"_errorMsg\";N;s:7:\"_errors\";a:0:{}}s:19:\"session.timer.start\";i:1256486013;s:18:\"session.timer.last\";i:1256486013;s:17:\"session.timer.now\";i:1256486016;}');
/*!40000 ALTER TABLE `jos_session` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `jos_stats_agents`
--

DROP TABLE IF EXISTS `jos_stats_agents`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `jos_stats_agents` (
  `agent` varchar(255) NOT NULL DEFAULT '',
  `type` tinyint(1) unsigned NOT NULL DEFAULT '0',
  `hits` int(11) unsigned NOT NULL DEFAULT '1'
) ENGINE=MyISAM DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `jos_stats_agents`
--

LOCK TABLES `jos_stats_agents` WRITE;
/*!40000 ALTER TABLE `jos_stats_agents` DISABLE KEYS */;
/*!40000 ALTER TABLE `jos_stats_agents` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `jos_templates_menu`
--

DROP TABLE IF EXISTS `jos_templates_menu`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `jos_templates_menu` (
  `template` varchar(255) NOT NULL DEFAULT '',
  `menuid` int(11) NOT NULL DEFAULT '0',
  `client_id` tinyint(4) NOT NULL DEFAULT '0',
  PRIMARY KEY (`menuid`,`client_id`,`template`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `jos_templates_menu`
--

LOCK TABLES `jos_templates_menu` WRITE;
/*!40000 ALTER TABLE `jos_templates_menu` DISABLE KEYS */;
INSERT INTO `jos_templates_menu` VALUES ('ja_purity',0,0),('khepri',0,1);
/*!40000 ALTER TABLE `jos_templates_menu` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `jos_users`
--

DROP TABLE IF EXISTS `jos_users`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `jos_users` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(255) NOT NULL DEFAULT '',
  `username` varchar(150) NOT NULL DEFAULT '',
  `email` varchar(100) NOT NULL DEFAULT '',
  `password` varchar(100) NOT NULL DEFAULT '',
  `usertype` varchar(25) NOT NULL DEFAULT '',
  `block` tinyint(4) NOT NULL DEFAULT '0',
  `sendEmail` tinyint(4) DEFAULT '0',
  `gid` tinyint(3) unsigned NOT NULL DEFAULT '1',
  `registerDate` datetime NOT NULL DEFAULT '0000-00-00 00:00:00',
  `lastvisitDate` datetime NOT NULL DEFAULT '0000-00-00 00:00:00',
  `activation` varchar(100) NOT NULL DEFAULT '',
  `params` text NOT NULL,
  PRIMARY KEY (`id`),
  KEY `usertype` (`usertype`),
  KEY `idx_name` (`name`),
  KEY `gid_block` (`gid`,`block`),
  KEY `username` (`username`),
  KEY `email` (`email`)
) ENGINE=MyISAM AUTO_INCREMENT=64 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `jos_users`
--

LOCK TABLES `jos_users` WRITE;
/*!40000 ALTER TABLE `jos_users` DISABLE KEYS */;
INSERT INTO `jos_users` VALUES (62,'Administrator','joom_admin','meet_ub@mail.ru','7e1c05fedfb10d48b20ce97fc974137e:YqwkhrjZ9Hc5WEAWx1629NzzIrk9KURR','Super Administrator',0,1,25,'2009-08-16 17:57:05','2009-10-25 14:22:23','','admin_language=\nlanguage=\neditor=\nhelpsite=\ntimezone=0\n\n'),(63,'test','user_tst','tmpprj@gmail.com','51a4f09c0610f5a9ad67c0629ab9869c:evxdapEtAxgfsM3TTZRlElW5a8aTIt6D','Registered',0,0,18,'2009-08-27 19:06:08','2009-10-25 14:03:40','','language=\ntimezone=0\n\n');
/*!40000 ALTER TABLE `jos_users` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `jos_weblinks`
--

DROP TABLE IF EXISTS `jos_weblinks`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `jos_weblinks` (
  `id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `catid` int(11) NOT NULL DEFAULT '0',
  `sid` int(11) NOT NULL DEFAULT '0',
  `title` varchar(250) NOT NULL DEFAULT '',
  `alias` varchar(255) NOT NULL DEFAULT '',
  `url` varchar(250) NOT NULL DEFAULT '',
  `description` text NOT NULL,
  `date` datetime NOT NULL DEFAULT '0000-00-00 00:00:00',
  `hits` int(11) NOT NULL DEFAULT '0',
  `published` tinyint(1) NOT NULL DEFAULT '0',
  `checked_out` int(11) NOT NULL DEFAULT '0',
  `checked_out_time` datetime NOT NULL DEFAULT '0000-00-00 00:00:00',
  `ordering` int(11) NOT NULL DEFAULT '0',
  `archived` tinyint(1) NOT NULL DEFAULT '0',
  `approved` tinyint(1) NOT NULL DEFAULT '1',
  `params` text NOT NULL,
  PRIMARY KEY (`id`),
  KEY `catid` (`catid`,`published`,`archived`)
) ENGINE=MyISAM AUTO_INCREMENT=7 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `jos_weblinks`
--

LOCK TABLES `jos_weblinks` WRITE;
/*!40000 ALTER TABLE `jos_weblinks` DISABLE KEYS */;
INSERT INTO `jos_weblinks` VALUES (1,2,0,'Joomla!','joomla','http://www.joomla.org','Home of Joomla!','2005-02-14 15:19:02',3,0,0,'0000-00-00 00:00:00',1,0,1,'target=0'),(2,2,0,'php.net','php','http://www.php.net','The language that Joomla! is developed in','2004-07-07 11:33:24',6,0,0,'0000-00-00 00:00:00',3,0,1,''),(3,2,0,'MySQL','mysql','http://www.mysql.com','The database that Joomla! uses','2004-07-07 10:18:31',1,0,0,'0000-00-00 00:00:00',5,0,1,''),(4,2,0,'OpenSourceMatters','opensourcematters','http://www.opensourcematters.org','Home of OSM','2005-02-14 15:19:02',11,0,0,'0000-00-00 00:00:00',2,0,1,'target=0'),(5,2,0,'Joomla! - Forums','joomla-forums','http://forum.joomla.org','Joomla! Forums','2005-02-14 15:19:02',4,0,0,'0000-00-00 00:00:00',4,0,1,'target=0'),(6,2,0,'Ohloh Tracking of Joomla!','ohloh-tracking-of-joomla','http://www.ohloh.net/projects/20','Objective reports from Ohloh about Joomla\'s development activity. Joomla! has some star developers with serious kudos.','2007-07-19 09:28:31',1,0,0,'0000-00-00 00:00:00',6,0,1,'target=0\n\n');
/*!40000 ALTER TABLE `jos_weblinks` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2009-10-25 19:07:40
