-- phpMyAdmin SQL Dump
-- version 5.2.0
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: Jun 24, 2024 at 04:15 PM
-- Server version: 10.4.27-MariaDB
-- PHP Version: 8.2.0

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `ucrs`
--

-- --------------------------------------------------------

--
-- Table structure for table `admin`
--

CREATE TABLE `admin` (
  `adminID` varchar(12) NOT NULL,
  `adminName` varchar(250) NOT NULL,
  `adminPhone` varchar(20) NOT NULL,
  `adminPassword` varchar(50) NOT NULL,
  `adminemail` varchar(250) NOT NULL,
  `adminmaster` varchar(25) NOT NULL,
  `adminaccess` int(12) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `admin`
--

INSERT INTO `admin` (`adminID`, `adminName`, `adminPhone`, `adminPassword`, `adminemail`, `adminmaster`, `adminaccess`) VALUES
('001', 'KIRTIGANBALU', '0147244210', 'a0e483030ee5c0ee4cb01ee23345de7f', 'kirtiganbalu85@gmail.com', 'Yes', 1),
('002', 'SHANKAR', '01121212718', 'a0e483030ee5c0ee4cb01ee23345de7f', 'shankarbalu28@gmail.com', 'Yes', 1),
('005', 'KIRTIGAN', '0147244210', 'a0e483030ee5c0ee4cb01ee23345de7f', 'kirtiganbalu85@gmail.com', 'No', 1);

-- --------------------------------------------------------

--
-- Table structure for table `booking`
--

CREATE TABLE `booking` (
  `bookingID` int(12) NOT NULL,
  `b_date` date NOT NULL,
  `b_timepickup` time NOT NULL,
  `b_timereturn` time NOT NULL,
  `b_totalamount` decimal(10,2) NOT NULL,
  `b_status` varchar(20) NOT NULL,
  `studentID` int(12) NOT NULL,
  `carID` int(12) NOT NULL,
  `car_number` varchar(10) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `booking`
--

INSERT INTO `booking` (`bookingID`, `b_date`, `b_timepickup`, `b_timereturn`, `b_totalamount`, `b_status`, `studentID`, `carID`, `car_number`) VALUES
(34, '2024-05-23', '11:00:00', '16:00:00', '15.00', 'CONFIRM', 7, 36, 'ASD1230'),
(35, '2024-05-23', '13:00:00', '21:00:00', '36.00', 'REJECT', 7, 34, 'ABC1234'),
(36, '2024-05-23', '12:00:00', '23:15:00', '51.63', 'CONFIRM', 7, 37, 'QWE1245'),
(37, '2024-06-04', '12:00:00', '13:30:00', '9.40', 'CONFIRM', 7, 35, 'BHQ1357'),
(38, '2024-06-04', '12:00:00', '16:30:00', '26.20', 'CONFIRM', 6, 35, 'BHQ1357'),
(39, '2024-06-04', '12:00:00', '15:00:00', '16.80', 'REJECT', 6, 35, 'BHQ1357'),
(40, '2024-06-04', '12:00:00', '14:30:00', '8.50', 'CONFIRM', 6, 36, 'ASD1230'),
(41, '2024-06-16', '12:00:00', '14:30:00', '16.50', 'CONFIRM', 6, 35, 'BHQ1357'),
(42, '2024-06-16', '12:00:00', '15:00:00', '13.50', 'REJECT', 6, 37, 'QWE1245'),
(43, '2024-06-18', '12:00:00', '16:00:00', '18.00', 'REJECT', 7, 34, 'ABC1234'),
(44, '2024-06-18', '12:00:00', '13:00:00', '3.00', 'REJECT', 6, 36, 'ASD1230'),
(45, '2024-06-19', '12:00:00', '18:30:00', '20.50', 'CONFIRM', 7, 36, 'ASD1230'),
(46, '2024-06-20', '12:00:00', '18:15:00', '19.75', 'CONFIRM', 6, 36, 'ASD1230'),
(47, '2024-06-20', '12:00:00', '14:00:00', '6.00', 'REJECT', 6, 36, 'ASD1230'),
(48, '2024-06-21', '12:00:00', '21:30:00', '28.50', 'REJECT', 6, 36, 'ASD1230'),
(50, '2024-06-20', '11:00:00', '16:30:00', '27.75', 'CONFIRM', 8, 37, 'QWE1245');

-- --------------------------------------------------------

--
-- Table structure for table `carowner`
--

CREATE TABLE `carowner` (
  `ownerID` int(12) NOT NULL,
  `ownerName` varchar(250) NOT NULL,
  `ownerage` int(3) NOT NULL,
  `ownerPhone` varchar(20) NOT NULL,
  `ownerGender` varchar(8) NOT NULL,
  `ownerPassword` varchar(50) NOT NULL,
  `ownerlicence` varchar(20) NOT NULL,
  `ownerIC` varchar(15) NOT NULL,
  `ownerstatus` varchar(25) NOT NULL,
  `owneraccess` int(12) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `carowner`
--

INSERT INTO `carowner` (`ownerID`, `ownerName`, `ownerage`, `ownerPhone`, `ownerGender`, `ownerPassword`, `ownerlicence`, `ownerIC`, `ownerstatus`, `owneraccess`) VALUES
(7, 'AJIM', 23, '0194243858', 'Male', 'a0e483030ee5c0ee4cb01ee23345de7f', 'lkiend', '020805100811', 'APPROVE', 0),
(8, 'ZUL', 26, '01131872599', 'Male', 'a0e483030ee5c0ee4cb01ee23345de7f', 'lskies', '020805100812', 'APPROVE', 1),
(9, 'SHANKAR', 26, '0147244211', 'Male', 'a0e483030ee5c0ee4cb01ee23345de7f', 'lkjhgfs', '020805100817', 'APPROVE', 1);

-- --------------------------------------------------------

--
-- Table structure for table `payment`
--

CREATE TABLE `payment` (
  `payID` int(12) NOT NULL,
  `pay_amount` decimal(10,2) NOT NULL,
  `pay_status` varchar(25) NOT NULL,
  `bookingID` int(12) NOT NULL,
  `studentID` int(12) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `payment`
--

INSERT INTO `payment` (`payID`, `pay_amount`, `pay_status`, `bookingID`, `studentID`) VALUES
(18, '70.10', 'REPAID', 33, 6),
(19, '15.00', 'REPAID', 34, 7),
(20, '51.63', 'REPAID', 36, 7),
(21, '9.40', 'REPAID', 37, 7),
(22, '26.20', 'REPAID', 38, 6),
(23, '8.50', 'REPAID', 40, 6),
(24, '16.50', 'REPAID', 41, 6),
(25, '20.50', 'REPAID', 45, 7),
(26, '19.75', 'REPAID', 46, 6),
(27, '27.75', 'REPAID', 50, 8);

-- --------------------------------------------------------

--
-- Table structure for table `rentalcar`
--

CREATE TABLE `rentalcar` (
  `carID` int(12) NOT NULL,
  `car_brand` varchar(25) NOT NULL,
  `car_year` year(4) NOT NULL,
  `car_model` varchar(25) NOT NULL,
  `car_units` int(12) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `rentalcar`
--

INSERT INTO `rentalcar` (`carID`, `car_brand`, `car_year`, `car_model`, `car_units`) VALUES
(34, 'HONDA', 2020, 'CITY', 1),
(35, 'PERODUA', 2015, 'MYVI', 1),
(36, 'PROTON', 2008, 'SAGA', 2),
(37, 'PROTON', 2010, 'WAJA', 1),
(38, 'HONDA', 2020, 'CIVIC', 1);

-- --------------------------------------------------------

--
-- Table structure for table `rentalcar_details`
--

CREATE TABLE `rentalcar_details` (
  `carID` int(12) NOT NULL,
  `car_number` varchar(10) NOT NULL,
  `car_type` varchar(25) NOT NULL,
  `car_transmission` varchar(25) NOT NULL,
  `car_roadtax` date NOT NULL,
  `car_rateper_hour` decimal(10,2) NOT NULL,
  `car_status` varchar(25) NOT NULL,
  `ownerID` int(12) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `rentalcar_details`
--

INSERT INTO `rentalcar_details` (`carID`, `car_number`, `car_type`, `car_transmission`, `car_roadtax`, `car_rateper_hour`, `car_status`, `ownerID`) VALUES
(34, 'ABC1234', 'SEDAN', 'AUTO', '2024-06-21', '4.50', 'AVAILABLE', 7),
(36, 'AGE7263', 'SEDAN', 'MANUAL', '2025-02-10', '6.00', 'AVAILABLE', 9),
(36, 'ASD1230', 'SUV', 'AUTO', '2025-06-29', '3.00', 'AVAILABLE', 8),
(35, 'BHQ1357', 'SUV', 'AUTO', '2024-06-19', '5.60', 'AVAILABLE', 7),
(38, 'KHS1785', 'SEDAN', 'AUTO', '2024-06-25', '7.50', 'AVAILABLE', 8),
(37, 'QWE1245', 'SEDAN', 'MANUAL', '2025-02-10', '4.50', 'AVAILABLE', 8);

--
-- Triggers `rentalcar_details`
--
DELIMITER $$
CREATE TRIGGER `update_units_trigger` AFTER INSERT ON `rentalcar_details` FOR EACH ROW BEGIN
    -- Update units column in rentalcar based on the count of records in rentalcar_details
    UPDATE rentalcar vm
    LEFT JOIN (
        SELECT carID, COUNT(*) AS total_records
        FROM rentalcar_details
        GROUP BY carID
    ) vd ON vm.carID = vd.carID
    SET vm.car_units = IFNULL(vd.total_records, 0);
END
$$
DELIMITER ;
DELIMITER $$
CREATE TRIGGER `update_units_trigger_after_delete` AFTER DELETE ON `rentalcar_details` FOR EACH ROW BEGIN
    -- Update units column in vehicle_master based on the count of records in vehicle_details
    UPDATE rentalcar vm
    LEFT JOIN (
        SELECT carID, COUNT(*) AS total_records
        FROM rentalcar_details
        GROUP BY carID
    ) vd ON vm.carID = vd.carID
    SET vm.car_units = IFNULL(vd.total_records, 0);
END
$$
DELIMITER ;
DELIMITER $$
CREATE TRIGGER `update_units_trigger_after_update` AFTER UPDATE ON `rentalcar_details` FOR EACH ROW BEGIN
    -- Update units column in vehicle_master based on the count of records in vehicle_details
    UPDATE rentalcar vm
    LEFT JOIN (
        SELECT carID, COUNT(*) AS total_records
        FROM rentalcar_details
        GROUP BY carID
    ) vd ON vm.carID = vd.carID
    SET vm.car_units = IFNULL(vd.total_records, 0);
END
$$
DELIMITER ;

-- --------------------------------------------------------

--
-- Table structure for table `student`
--

CREATE TABLE `student` (
  `studentID` int(12) NOT NULL,
  `studentName` varchar(250) NOT NULL,
  `studentgender` varchar(8) NOT NULL,
  `studentPhone` varchar(20) NOT NULL,
  `studentage` int(3) NOT NULL,
  `studentMatric` varchar(20) NOT NULL,
  `studentSemester` int(2) NOT NULL,
  `studentlicence` varchar(20) NOT NULL,
  `studentPassword` varchar(50) NOT NULL,
  `studentaccess` int(12) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `student`
--

INSERT INTO `student` (`studentID`, `studentName`, `studentgender`, `studentPhone`, `studentage`, `studentMatric`, `studentSemester`, `studentlicence`, `studentPassword`, `studentaccess`) VALUES
(6, 'yusryzam', 'Male', '01117752940', 22, 'B032310871', 3, 'astheks', 'a0e483030ee5c0ee4cb01ee23345de7f', 1),
(7, 'sarvind', 'Male', '0176097106', 22, 'B032310874', 3, 'lskikw', 'a0e483030ee5c0ee4cb01ee23345de7f', 0),
(8, 'madhan', 'Female', '0147244213', 25, 'B032310873', 3, 'lkjhf', 'a0e483030ee5c0ee4cb01ee23345de7f', 1);

--
-- Indexes for dumped tables
--

--
-- Indexes for table `admin`
--
ALTER TABLE `admin`
  ADD PRIMARY KEY (`adminID`);

--
-- Indexes for table `booking`
--
ALTER TABLE `booking`
  ADD PRIMARY KEY (`bookingID`),
  ADD KEY `studentID` (`studentID`),
  ADD KEY `b_carID` (`carID`);

--
-- Indexes for table `carowner`
--
ALTER TABLE `carowner`
  ADD PRIMARY KEY (`ownerID`);

--
-- Indexes for table `payment`
--
ALTER TABLE `payment`
  ADD PRIMARY KEY (`payID`),
  ADD KEY `bookingID` (`bookingID`),
  ADD KEY `pstudentID` (`studentID`);

--
-- Indexes for table `rentalcar`
--
ALTER TABLE `rentalcar`
  ADD PRIMARY KEY (`carID`);

--
-- Indexes for table `rentalcar_details`
--
ALTER TABLE `rentalcar_details`
  ADD PRIMARY KEY (`car_number`),
  ADD KEY `carID` (`carID`),
  ADD KEY `ownerID` (`ownerID`);

--
-- Indexes for table `student`
--
ALTER TABLE `student`
  ADD PRIMARY KEY (`studentID`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `booking`
--
ALTER TABLE `booking`
  MODIFY `bookingID` int(12) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=51;

--
-- AUTO_INCREMENT for table `carowner`
--
ALTER TABLE `carowner`
  MODIFY `ownerID` int(12) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=10;

--
-- AUTO_INCREMENT for table `payment`
--
ALTER TABLE `payment`
  MODIFY `payID` int(12) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=28;

--
-- AUTO_INCREMENT for table `rentalcar`
--
ALTER TABLE `rentalcar`
  MODIFY `carID` int(12) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=39;

--
-- AUTO_INCREMENT for table `student`
--
ALTER TABLE `student`
  MODIFY `studentID` int(12) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=9;

--
-- Constraints for dumped tables
--

--
-- Constraints for table `booking`
--
ALTER TABLE `booking`
  ADD CONSTRAINT `b_carID` FOREIGN KEY (`carID`) REFERENCES `rentalcar` (`carID`) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT `studentID` FOREIGN KEY (`studentID`) REFERENCES `student` (`studentID`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Constraints for table `payment`
--
ALTER TABLE `payment`
  ADD CONSTRAINT `bookingID` FOREIGN KEY (`bookingID`) REFERENCES `booking` (`bookingID`) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT `pstudentID` FOREIGN KEY (`studentID`) REFERENCES `student` (`studentID`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Constraints for table `rentalcar_details`
--
ALTER TABLE `rentalcar_details`
  ADD CONSTRAINT `carID` FOREIGN KEY (`carID`) REFERENCES `rentalcar` (`carID`) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT `ownerID` FOREIGN KEY (`ownerID`) REFERENCES `carowner` (`ownerID`) ON DELETE CASCADE ON UPDATE CASCADE;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
