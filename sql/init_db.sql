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
-- Table structure for table `__calibration`
--

DROP TABLE IF EXISTS `__calibration`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `__calibration` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(50) DEFAULT NULL,
  `type` int(11) DEFAULT NULL COMMENT 'Тип градуировки',
  `source` int(11) DEFAULT NULL,
  `interpolation` int(11) DEFAULT NULL,
  `active` tinyint(1) DEFAULT NULL,
  `date` date DEFAULT NULL,
  `description` varchar(256) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_uca1400_ai_ci COMMENT='Градуировки';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `__calibration`
--

LOCK TABLES `__calibration` WRITE;
/*!40000 ALTER TABLE `__calibration` DISABLE KEYS */;
INSERT INTO `__calibration` VALUES
(1,'first',2,1,1,1,'2026-06-11','');
/*!40000 ALTER TABLE `__calibration` ENABLE KEYS */;
UNLOCK TABLES;

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
(1,3,'lcard1','127.0.0.1',11111,NULL),
(3,2,'lcard2','127.0.0.1',11111,NULL);
/*!40000 ALTER TABLE `crate` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `experiment`
--

DROP TABLE IF EXISTS `experiment`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `experiment` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(50) NOT NULL,
  `startDate` datetime DEFAULT NULL,
  `stopDate` datetime DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_uca1400_ai_ci COMMENT='Эксперимент';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `experiment`
--

LOCK TABLES `experiment` WRITE;
/*!40000 ALTER TABLE `experiment` DISABLE KEYS */;
INSERT INTO `experiment` VALUES
(1,'TEST1','2023-06-15 06:02:45',NULL),
(2,'TEST2',NULL,NULL),
(4,'тест 3',NULL,NULL);
/*!40000 ALTER TABLE `experiment` ENABLE KEYS */;
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
) ENGINE=InnoDB AUTO_INCREMENT=541 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_uca1400_ai_ci COMMENT='Единицы измерений';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `measureunit`
--

LOCK TABLES `measureunit` WRITE;
/*!40000 ALTER TABLE `measureunit` DISABLE KEYS */;
INSERT INTO `measureunit` VALUES
(406,'Гц'),
(407,'В'),
(408,'Ом'),
(409,'А'),
(410,'мА'),
(411,'Вт'),
(412,'кВт'),
(413,'эрг/с'),
(414,'кал/с'),
(415,'°С'),
(416,'К'),
(417,'л/с'),
(418,'мл/с'),
(419,'м³/с'),
(420,'Па'),
(421,'бар'),
(422,'мм рт.ст.'),
(423,'атм'),
(424,'ат'),
(425,'ати'),
(426,'ата'),
(427,'кг/с'),
(428,'г/с'),
(429,'мг/с'),
(430,'Па·с'),
(431,'бар·с'),
(432,'мм рт.ст.·с'),
(433,'атм·с'),
(434,'ат·с'),
(435,'ати·с'),
(436,'ата·с'),
(437,'м'),
(438,'мм'),
(439,'см'),
(440,'дюйм'),
(441,'г/л'),
(442,'кг/м³'),
(443,'мг/см³'),
(444,'кг'),
(445,'г'),
(446,'мг'),
(447,'м²'),
(448,'мм²'),
(449,'см²'),
(450,'кв.дюйм'),
(451,'м/с'),
(452,'мм/с'),
(453,'см/с'),
(454,'дюйм/с'),
(455,'с'),
(456,'мс'),
(457,'мин'),
(458,'ч'),
(459,'Дж'),
(460,'эрг'),
(461,'кВт·ч'),
(462,'кал'),
(463,'ккал'),
(464,'м³'),
(465,'мм³'),
(466,'см³'),
(467,'л'),
(468,'кгс'),
(469,'гс'),
(470,'тс'),
(471,'мВ'),
(472,'МПа'),
(473,'Угловых °'),
(474,'Рад'),
(475,'об/мин'),
(476,'Без размерности'),
(477,'кгс/см²'),
(478,'%'),
(479,'°F'),
(480,'гПа'),
(481,'кПа'),
(482,'мбар'),
(483,'мм вод. ст.'),
(484,'psi'),
(485,'км/ч'),
(486,'мкм/с'),
(487,'м/с²'),
(488,'мм/с²'),
(489,'g'),
(490,'м³/мин'),
(491,'м³/ч'),
(492,'л/мин'),
(493,'л/ч'),
(494,'кг/мин'),
(495,'кг/ч'),
(496,'т/с'),
(497,'т/мин'),
(498,'т/ч'),
(499,'мкг'),
(500,'т'),
(501,'Н'),
(502,'кН'),
(503,'МВт'),
(504,'ккал/с'),
(505,'мкс'),
(506,'об/с'),
(507,'рад/с'),
(508,'мкВ'),
(509,'кВ'),
(510,'мкА'),
(511,'кА'),
(512,'кОм'),
(513,'МОм'),
(514,'ГОм'),
(515,'мОм'),
(516,'кГц'),
(517,'МГц'),
(518,'кДж'),
(519,'МПа'),
(520,'кПа'),
(521,'Па'),
(522,'г/м³'),
(523,'мкм'),
(524,'км'),
(525,'м/м'),
(526,'мм/м'),
(527,'мкм/м'),
(528,'мВ/В'),
(529,'Кл'),
(530,'пКл'),
(531,'кгс/см²'),
(532,'кгс/мм²'),
(533,'м'),
(534,'мм'),
(535,'см'),
(536,'дюйм'),
(537,'мкм'),
(538,'км'),
(539,'рад'),
(540,'°');
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
(1,1,11,'ltr11',NULL),
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
  `sn` varchar(50) DEFAULT NULL,
  `active` tinyint(1) DEFAULT NULL,
  `description` varchar(256) DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `sensor_sensortype_FK` (`sensortype_id`),
  CONSTRAINT `sensor_sensortype_FK` FOREIGN KEY (`sensortype_id`) REFERENCES `sensortype` (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_uca1400_ai_ci COMMENT='Датчики';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `sensor`
--

LOCK TABLES `sensor` WRITE;
/*!40000 ALTER TABLE `sensor` DISABLE KEYS */;
INSERT INTO `sensor` VALUES
(1,1,'NAME',1,NULL),
(2,1,'',0,NULL),
(3,1,'123',1,NULL);
/*!40000 ALTER TABLE `sensor` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `sensorcalibration`
--

DROP TABLE IF EXISTS `sensorcalibration`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `sensorcalibration` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `sensor_id` int(11) DEFAULT NULL,
  `index` smallint(6) DEFAULT NULL,
  `x` double DEFAULT NULL,
  `y` double DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `sensorcalibration_sensor_FK` (`sensor_id`),
  CONSTRAINT `sensor_calibration_sensor_FK` FOREIGN KEY (`sensor_id`) REFERENCES `sensor` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_uca1400_ai_ci COMMENT='Градуировки (значения) датчика индивидуальные';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `sensorcalibration`
--

LOCK TABLES `sensorcalibration` WRITE;
/*!40000 ALTER TABLE `sensorcalibration` DISABLE KEYS */;
INSERT INTO `sensorcalibration` VALUES
(1,1,1,2,3),
(2,1,0,2.5,3.2);
/*!40000 ALTER TABLE `sensorcalibration` ENABLE KEYS */;
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
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_uca1400_ai_ci COMMENT='Типы датчиков';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `sensortype`
--

LOCK TABLES `sensortype` WRITE;
/*!40000 ALTER TABLE `sensortype` DISABLE KEYS */;
INSERT INTO `sensortype` VALUES
(1,'TEST',1,2,3,'description'),
(2,'TEST2',0,0,0,NULL);
/*!40000 ALTER TABLE `sensortype` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `sensortypecalibration`
--

DROP TABLE IF EXISTS `sensortypecalibration`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `sensortypecalibration` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `sensortype_id` int(11) DEFAULT NULL,
  `x` double DEFAULT NULL,
  `y` double DEFAULT NULL,
  PRIMARY KEY (`id`),
  CONSTRAINT `sensortypecalibration_sensortype_FK` FOREIGN KEY (`id`) REFERENCES `sensortype` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_uca1400_ai_ci COMMENT='Градуировки (значения) датчика типовые';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `sensortypecalibration`
--

LOCK TABLES `sensortypecalibration` WRITE;
/*!40000 ALTER TABLE `sensortypecalibration` DISABLE KEYS */;
/*!40000 ALTER TABLE `sensortypecalibration` ENABLE KEYS */;
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

-- Dump completed on 2026-06-29 16:31:15
