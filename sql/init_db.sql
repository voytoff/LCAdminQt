/*M!999999\- enable the sandbox mode */
-- MariaDB dump 10.19-11.7.2-MariaDB, for Win64 (AMD64)
--
-- Host: 192.168.10.213    Database: 106org
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
  `calibration` smallint(6) DEFAULT NULL COMMENT 'Используемая с датчиком градуировка',
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
(1,1,'NAME',1,1,NULL),
(2,1,'',2,0,NULL),
(3,1,'123',1,1,NULL);
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
) ENGINE=InnoDB AUTO_INCREMENT=114 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_uca1400_ai_ci COMMENT='Градуировки (значения) датчика индивидуальные';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `sensorcalibration`
--

LOCK TABLES `sensorcalibration` WRITE;
/*!40000 ALTER TABLE `sensorcalibration` DISABLE KEYS */;
INSERT INTO `sensorcalibration` VALUES
(44,2,0,11.76,60),
(45,2,1,13.828,65),
(46,2,2,15.94,70),
(47,2,3,16.793,72),
(48,2,4,17.65,74),
(49,2,5,18.509,76),
(50,2,6,19.371,78),
(51,2,7,20.235,80),
(52,2,8,21.099,82),
(53,2,9,21.964,84),
(54,2,10,22.829,86),
(55,2,11,23.695,88),
(56,2,12,24.56,90),
(57,2,13,25.425,92),
(58,2,14,26.289,94),
(59,2,15,27.153,96),
(60,2,16,28.015,98),
(61,2,17,28.877,100),
(62,2,18,33.168,110),
(63,2,19,37.429,120),
(64,2,20,41.658,130),
(65,2,21,45.86,140),
(66,2,22,50.035,150),
(67,2,23,54.187,160),
(68,2,24,58.318,170),
(69,2,25,62.431,180),
(70,2,26,66.526,190),
(71,2,27,70.604,200),
(72,2,28,74.667,210),
(73,2,29,78.716,220),
(74,2,30,82.751,230),
(75,2,31,86.773,240),
(76,2,32,90.782,250),
(77,2,33,94.779,260),
(78,2,34,100.02,273.15),
(79,2,35,102.736,280),
(80,2,36,106.692,290),
(81,2,37,110.636,300),
(82,2,38,114.568,310),
(83,2,39,118.488,320),
(84,2,40,122.397,330),
(85,3,0,11.7,60),
(86,3,1,13.77,65),
(87,3,2,15.883,70),
(88,3,3,20.181,80),
(89,3,4,21.046,82),
(90,3,5,21.911,84),
(91,3,6,22.777,86),
(92,3,7,23.643,88),
(93,3,8,24.509,90),
(94,3,9,25.375,92),
(95,3,10,26.24,94),
(96,3,11,27.104,96),
(97,3,12,27.967,98),
(98,3,13,28.829,100),
(99,3,14,30.98,105),
(100,3,15,33.123,110),
(101,3,16,35.259,115),
(102,3,17,37.386,120),
(103,3,18,45.823,140),
(104,3,19,54.165,160),
(105,3,20,62.405,180),
(106,3,21,70.584,200),
(107,3,22,78.702,220),
(108,3,23,86.764,240),
(109,3,24,94.775,260),
(110,3,25,100.02,273.15),
(111,3,26,102.736,280),
(112,3,27,110.636,300),
(113,3,28,118.488,320);
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
(1,'TEST',1,1,3,'description'),
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
  `index` smallint(6) DEFAULT NULL,
  `x` double DEFAULT NULL,
  `y` double DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `sensortypecalibration_sensortype_FK` (`sensortype_id`),
  CONSTRAINT `sensortypecalibration_sensortype_FK` FOREIGN KEY (`sensortype_id`) REFERENCES `sensortype` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=46 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_uca1400_ai_ci COMMENT='Градуировки (значения) датчика типовые';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `sensortypecalibration`
--

LOCK TABLES `sensortypecalibration` WRITE;
/*!40000 ALTER TABLE `sensortypecalibration` DISABLE KEYS */;
INSERT INTO `sensortypecalibration` VALUES
(1,1,0,11.7,60),
(2,1,1,13.77,65),
(5,2,0,11.768,60),
(6,2,1,13.834,65),
(7,2,2,15.946,70),
(8,2,3,16.799,72),
(9,2,4,17.655,74),
(10,2,5,18.514,76),
(11,2,6,19.376,78),
(12,2,7,20.239,80),
(13,2,8,21.103,82),
(14,2,9,21.967,84),
(15,2,10,22.832,86),
(16,2,11,23.697,88),
(17,2,12,24.562,90),
(18,2,13,25.427,92),
(19,2,14,26.291,94),
(20,2,15,27.154,96),
(21,2,16,28.016,98),
(22,2,17,28.877,100),
(23,2,18,33.167,110),
(24,2,19,37.425,120),
(25,2,20,41.653,130),
(26,2,21,45.853,140),
(27,2,22,50.026,150),
(28,2,23,54.177,160),
(29,2,24,58.306,170),
(30,2,25,62.417,180),
(31,2,26,66.51,190),
(32,2,27,70.587,200),
(33,2,28,74.648,210),
(34,2,29,78.695,220),
(35,2,30,82.729,230),
(36,2,31,86.749,240),
(37,2,32,90.756,250),
(38,2,33,94.751,260),
(39,2,34,99.99,273.15),
(40,2,35,102.706,280),
(41,2,36,106.66,290),
(42,2,37,110.603,300),
(43,2,38,114.534,310),
(44,2,39,118.453,320),
(45,2,40,122.361,330);
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

-- Dump completed on 2026-06-30 16:25:11
