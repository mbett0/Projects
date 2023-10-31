-- phpMyAdmin SQL Dump
-- version 5.1.2
-- https://www.phpmyadmin.net/
--
-- Host: localhost:3306
-- Generation Time: Oct 31, 2023 at 12:17 AM
-- Server version: 5.7.24
-- PHP Version: 8.0.1

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `jbmfg_parts`
--

-- --------------------------------------------------------

--
-- Table structure for table `parts`
--

CREATE TABLE `parts` (
  `PartNumber` varchar(255) NOT NULL,
  `PDF` varchar(255) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `parts`
--

INSERT INTO `parts` (`PartNumber`, `PDF`) VALUES
('0', 'nope'),
('00011955 rev 0', '1'),
('0001923-Balls', 'www.google.drive.com/fowijafoin'),
('002i15012049f', 'wo39qpoj'),
('09q750937', 'aijefoinew'),
('11955', 'yuu'),
('39510-B', 'C:\\Users\\mikem\\Downloads\\ComputerGraphics\\ComputerGraphics_C++\\hw-9\\Resume.pdf'),
('4221', 'C:\\Users\\mikem\\Downloads\\ResumeMichaelB.pdf'),
('53151', 'he'),
('58129', '\"C:\\Users\\mikem\\Downloads\\ComputerGraphics\\ComputerGraphics_C++\\hw-9\\Resume.pdf\"'),
('68959', 'no');

-- --------------------------------------------------------

--
-- Table structure for table `quotesandinvoices`
--

CREATE TABLE `quotesandinvoices` (
  `orderID` int(11) NOT NULL,
  `Date` varchar(15) NOT NULL,
  `Quantity` int(11) NOT NULL,
  `UnitPrice` double NOT NULL,
  `Customer` varchar(250) NOT NULL,
  `QuoteOrOrder` int(11) NOT NULL,
  `parts_PartNumber` varchar(255) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `quotesandinvoices`
--

INSERT INTO `quotesandinvoices` (`orderID`, `Date`, `Quantity`, `UnitPrice`, `Customer`, `QuoteOrOrder`, `parts_PartNumber`) VALUES
(1, '2023-10-12', 500, 5.62, 'Davis Consulting Firm', 1, '53151'),
(3, '2023-10-19', 10, 0, 'Dave', 0, '4221'),
(4, '2023-10-19', 50, 0, 'tim', 0, '4221'),
(5, '2023-10-19', 700, 5.88, 'Billy Benson', 1, '58129'),
(6, '2023-10-19', 5, 191, 'db control', 1, '00011955 rev 0'),
(9, '2023-10-26', 7000, 851.11, 'Davis and David INC', 0, '53151');

--
-- Indexes for dumped tables
--

--
-- Indexes for table `parts`
--
ALTER TABLE `parts`
  ADD PRIMARY KEY (`PartNumber`);

--
-- Indexes for table `quotesandinvoices`
--
ALTER TABLE `quotesandinvoices`
  ADD PRIMARY KEY (`orderID`,`parts_PartNumber`),
  ADD KEY `fk_quotesAndInvoices_parts_idx` (`parts_PartNumber`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `quotesandinvoices`
--
ALTER TABLE `quotesandinvoices`
  MODIFY `orderID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=10;

--
-- Constraints for dumped tables
--

--
-- Constraints for table `quotesandinvoices`
--
ALTER TABLE `quotesandinvoices`
  ADD CONSTRAINT `fk_quotesAndInvoices_parts` FOREIGN KEY (`parts_PartNumber`) REFERENCES `parts` (`PartNumber`) ON DELETE NO ACTION ON UPDATE NO ACTION;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
