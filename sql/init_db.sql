/*M!999999\- enable the sandbox mode */
-- MariaDB dump 10.19-11.7.2-MariaDB, for Win64 (AMD64)
--
-- Host: localhost    Database: 106org
-- ------------------------------------------------------
-- Server version	12.3.2-MariaDB

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*M!100616 SET @OLD_NOTE_VERBOSITY=@@NOTE_VERBOSITY, NOTE_VERBOSITY=0 */;

--
-- Table structure for table `__cratetype`
--

DROP TABLE IF EXISTS `__cratetype`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `__cratetype` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(50) DEFAULT NULL,
  `interface` tinyint(4) DEFAULT NULL COMMENT 'Интерфейс',
  `slots` int(11) DEFAULT NULL COMMENT 'Количество слотов',
  `description` varchar(256) DEFAULT NULL COMMENT 'Описание',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_uca1400_ai_ci COMMENT='Типы крейтов';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `__cratetype`
--

LOCK TABLES `__cratetype` WRITE;
/*!40000 ALTER TABLE `__cratetype` DISABLE KEYS */;
INSERT INTO `__cratetype` VALUES
(1,'LTR-EU-16',NULL,16,'16-местный крейт с интерфейсами USB 2.0, Ethernet и источником питания.');
/*!40000 ALTER TABLE `__cratetype` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `__moduletype`
--

DROP TABLE IF EXISTS `__moduletype`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `__moduletype` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(50) DEFAULT NULL,
  `depth` int(11) DEFAULT NULL,
  `interface` smallint(11) DEFAULT NULL,
  `description` varchar(256) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_uca1400_ai_ci COMMENT='Типы модулей';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `__moduletype`
--

LOCK TABLES `__moduletype` WRITE;
/*!40000 ALTER TABLE `__moduletype` DISABLE KEYS */;
INSERT INTO `__moduletype` VALUES
(1,'LTR11',14,11,'Универсальный модуль АЦП с последовательным опросом каналов');
/*!40000 ALTER TABLE `__moduletype` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `calibration`
--

DROP TABLE IF EXISTS `calibration`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `calibration` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(50) DEFAULT NULL,
  `source` int(11) DEFAULT NULL,
  `type` int(11) DEFAULT NULL,
  `active` tinyint(1) DEFAULT NULL,
  `date` date DEFAULT NULL,
  `description` varchar(256) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_uca1400_ai_ci COMMENT='Градуировки';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `calibration`
--

LOCK TABLES `calibration` WRITE;
/*!40000 ALTER TABLE `calibration` DISABLE KEYS */;
INSERT INTO `calibration` VALUES
(1,'first',NULL,NULL,1,'2026-06-11',NULL);
/*!40000 ALTER TABLE `calibration` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `crate`
--

DROP TABLE IF EXISTS `crate`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `crate` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `cratetype` int(11) DEFAULT NULL,
  `name` varchar(50) DEFAULT NULL,
  `host` varchar(20) DEFAULT '127.0.0.1',
  `port` int(11) DEFAULT 11111,
  `description` varchar(256) DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `crate_cratetype_FK` (`cratetype`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci COMMENT='Таблица крейтов';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `crate`
--

LOCK TABLES `crate` WRITE;
/*!40000 ALTER TABLE `crate` DISABLE KEYS */;
INSERT INTO `crate` VALUES
(1,3,'lcard1','127.0.0.1',11113,NULL),
(3,2,'lcard2','127.0.0.1',11111,NULL);
/*!40000 ALTER TABLE `crate` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `measureunit`
--

DROP TABLE IF EXISTS `measureunit`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `measureunit` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(50) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=406 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_uca1400_ai_ci COMMENT='Единицы измерений';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `measureunit`
--

LOCK TABLES `measureunit` WRITE;
/*!40000 ALTER TABLE `measureunit` DISABLE KEYS */;
INSERT INTO `measureunit` VALUES
(271,'Гц'),
(272,'В'),
(273,'Ом'),
(274,'А'),
(275,'мА'),
(276,'Вт'),
(277,'кВт'),
(278,'эрг/с'),
(279,'кал/с'),
(280,'°С'),
(281,'К'),
(282,'л/с'),
(283,'мл/с'),
(284,'м³/с'),
(285,'Па'),
(286,'бар'),
(287,'мм рт.ст.'),
(288,'атм'),
(289,'ат'),
(290,'ати'),
(291,'ата'),
(292,'кг/с'),
(293,'г/с'),
(294,'мг/с'),
(295,'Па·с'),
(296,'бар·с'),
(297,'мм рт.ст.·с'),
(298,'атм·с'),
(299,'ат·с'),
(300,'ати·с'),
(301,'ата·с'),
(302,'м'),
(303,'мм'),
(304,'см'),
(305,'дюйм'),
(306,'г/л'),
(307,'кг/м³'),
(308,'мг/см³'),
(309,'кг'),
(310,'г'),
(311,'мг'),
(312,'м²'),
(313,'мм²'),
(314,'см²'),
(315,'кв.дюйм'),
(316,'м/с'),
(317,'мм/с'),
(318,'см/с'),
(319,'дюйм/с'),
(320,'с'),
(321,'мс'),
(322,'мин'),
(323,'ч'),
(324,'Дж'),
(325,'эрг'),
(326,'кВт·ч'),
(327,'кал'),
(328,'ккал'),
(329,'м³'),
(330,'мм³'),
(331,'см³'),
(332,'л'),
(333,'кгс'),
(334,'гс'),
(335,'тс'),
(336,'мВ'),
(337,'МПа'),
(338,'Угловых °'),
(339,'Рад'),
(340,'об/мин'),
(341,'Без размерности'),
(342,'кгс/см²'),
(343,'%'),
(344,'°F'),
(345,'гПа'),
(346,'кПа'),
(347,'мбар'),
(348,'мм вод. ст.'),
(349,'psi'),
(350,'км/ч'),
(351,'мкм/с'),
(352,'м/с²'),
(353,'мм/с²'),
(354,'g'),
(355,'м³/мин'),
(356,'м³/ч'),
(357,'л/мин'),
(358,'л/ч'),
(359,'кг/мин'),
(360,'кг/ч'),
(361,'т/с'),
(362,'т/мин'),
(363,'т/ч'),
(364,'мкг'),
(365,'т'),
(366,'Н'),
(367,'кН'),
(368,'МВт'),
(369,'ккал/с'),
(370,'мкс'),
(371,'об/с'),
(372,'рад/с'),
(373,'мкВ'),
(374,'кВ'),
(375,'мкА'),
(376,'кА'),
(377,'кОм'),
(378,'МОм'),
(379,'ГОм'),
(380,'мОм'),
(381,'кГц'),
(382,'МГц'),
(383,'кДж'),
(384,'МПа'),
(385,'кПа'),
(386,'Па'),
(387,'г/м³'),
(388,'мкм'),
(389,'км'),
(390,'м/м'),
(391,'мм/м'),
(392,'мкм/м'),
(393,'мВ/В'),
(394,'Кл'),
(395,'пКл'),
(396,'кгс/см²'),
(397,'кгс/мм²'),
(398,'м'),
(399,'мм'),
(400,'см'),
(401,'дюйм'),
(402,'мкм'),
(403,'км'),
(404,'рад'),
(405,'°');
/*!40000 ALTER TABLE `measureunit` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `module`
--

DROP TABLE IF EXISTS `module`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `module` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `crate_id` int(11) DEFAULT NULL COMMENT 'Связующий столбец с таблицей crate',
  `moduletype` int(11) DEFAULT NULL,
  `name` varchar(50) NOT NULL DEFAULT '',
  `description` varchar(256) DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `FK_crate_module` (`crate_id`),
  KEY `module_moduletype_FK` (`moduletype`)
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_uca1400_ai_ci COMMENT='LTR-модуль крейта';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `module`
--

LOCK TABLES `module` WRITE;
/*!40000 ALTER TABLE `module` DISABLE KEYS */;
INSERT INTO `module` VALUES
(1,1,1,'ltr11',NULL),
(2,3,NULL,'ltr114',NULL);
/*!40000 ALTER TABLE `module` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `sensor`
--

DROP TABLE IF EXISTS `sensor`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `sensor` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `sensortype_id` int(11) DEFAULT NULL,
  `calibration_id` int(11) DEFAULT NULL,
  `sn` varchar(50) DEFAULT NULL,
  `active` tinyint(1) DEFAULT NULL,
  `description` varchar(256) DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `sensor_sensortype_FK` (`sensortype_id`),
  KEY `sensor_calibration_FK` (`calibration_id`),
  CONSTRAINT `sensor_calibration_FK` FOREIGN KEY (`calibration_id`) REFERENCES `calibration` (`id`),
  CONSTRAINT `sensor_sensortype_FK` FOREIGN KEY (`sensortype_id`) REFERENCES `sensortype` (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_uca1400_ai_ci COMMENT='Датчики';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `sensor`
--

LOCK TABLES `sensor` WRITE;
/*!40000 ALTER TABLE `sensor` DISABLE KEYS */;
INSERT INTO `sensor` VALUES
(1,1,1,'NAME',0,NULL);
/*!40000 ALTER TABLE `sensor` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `sensortype`
--

DROP TABLE IF EXISTS `sensortype`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `sensortype` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(100) DEFAULT NULL,
  `type` int(11) DEFAULT NULL,
  `source` int(11) DEFAULT NULL,
  `interpolation` int(11) DEFAULT NULL,
  `description` varchar(256) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_uca1400_ai_ci COMMENT='Типы датчиков';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `sensortype`
--

LOCK TABLES `sensortype` WRITE;
/*!40000 ALTER TABLE `sensortype` DISABLE KEYS */;
INSERT INTO `sensortype` VALUES
(1,'TEST',1,2,3,'description');
/*!40000 ALTER TABLE `sensortype` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping routines for database '106org'
--
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*M!100616 SET NOTE_VERBOSITY=@OLD_NOTE_VERBOSITY */;

-- Dump completed on 2026-06-24 16:20:08
