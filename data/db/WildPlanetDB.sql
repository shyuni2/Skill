USE [master]
GO
/****** Object:  Database [WildPlanetDB]    Script Date: 10/29/2018 19:50:19 ******/
CREATE DATABASE [WildPlanetDB] ON  PRIMARY 
( NAME = N'WildPlanetDB', FILENAME = N'D:\01_TBasis2D\db\DB\WildPlanetDB.mdf' , SIZE = 5120KB , MAXSIZE = UNLIMITED, FILEGROWTH = 5120KB )
 LOG ON 
( NAME = N'WildPlanetDB_log', FILENAME = N'D:\01_TBasis2D\db\DB\WildPlanetDB_log.ldf' , SIZE = 1024KB , MAXSIZE = 2048GB , FILEGROWTH = 10%)
GO
ALTER DATABASE [WildPlanetDB] SET COMPATIBILITY_LEVEL = 100
GO
IF (1 = FULLTEXTSERVICEPROPERTY('IsFullTextInstalled'))
begin
EXEC [WildPlanetDB].[dbo].[sp_fulltext_database] @action = 'enable'
end
GO
ALTER DATABASE [WildPlanetDB] SET ANSI_NULL_DEFAULT OFF
GO
ALTER DATABASE [WildPlanetDB] SET ANSI_NULLS OFF
GO
ALTER DATABASE [WildPlanetDB] SET ANSI_PADDING OFF
GO
ALTER DATABASE [WildPlanetDB] SET ANSI_WARNINGS OFF
GO
ALTER DATABASE [WildPlanetDB] SET ARITHABORT OFF
GO
ALTER DATABASE [WildPlanetDB] SET AUTO_CLOSE OFF
GO
ALTER DATABASE [WildPlanetDB] SET AUTO_CREATE_STATISTICS ON
GO
ALTER DATABASE [WildPlanetDB] SET AUTO_SHRINK OFF
GO
ALTER DATABASE [WildPlanetDB] SET AUTO_UPDATE_STATISTICS ON
GO
ALTER DATABASE [WildPlanetDB] SET CURSOR_CLOSE_ON_COMMIT OFF
GO
ALTER DATABASE [WildPlanetDB] SET CURSOR_DEFAULT  GLOBAL
GO
ALTER DATABASE [WildPlanetDB] SET CONCAT_NULL_YIELDS_NULL OFF
GO
ALTER DATABASE [WildPlanetDB] SET NUMERIC_ROUNDABORT OFF
GO
ALTER DATABASE [WildPlanetDB] SET QUOTED_IDENTIFIER OFF
GO
ALTER DATABASE [WildPlanetDB] SET RECURSIVE_TRIGGERS OFF
GO
ALTER DATABASE [WildPlanetDB] SET  DISABLE_BROKER
GO
ALTER DATABASE [WildPlanetDB] SET AUTO_UPDATE_STATISTICS_ASYNC OFF
GO
ALTER DATABASE [WildPlanetDB] SET DATE_CORRELATION_OPTIMIZATION OFF
GO
ALTER DATABASE [WildPlanetDB] SET TRUSTWORTHY OFF
GO
ALTER DATABASE [WildPlanetDB] SET ALLOW_SNAPSHOT_ISOLATION OFF
GO
ALTER DATABASE [WildPlanetDB] SET PARAMETERIZATION SIMPLE
GO
ALTER DATABASE [WildPlanetDB] SET READ_COMMITTED_SNAPSHOT OFF
GO
ALTER DATABASE [WildPlanetDB] SET HONOR_BROKER_PRIORITY OFF
GO
ALTER DATABASE [WildPlanetDB] SET  READ_WRITE
GO
ALTER DATABASE [WildPlanetDB] SET RECOVERY SIMPLE
GO
ALTER DATABASE [WildPlanetDB] SET  MULTI_USER
GO
ALTER DATABASE [WildPlanetDB] SET PAGE_VERIFY CHECKSUM
GO
ALTER DATABASE [WildPlanetDB] SET DB_CHAINING OFF
GO
USE [WildPlanetDB]
GO
/****** Object:  User [WP]    Script Date: 10/29/2018 19:50:19 ******/
CREATE USER [WP] WITHOUT LOGIN WITH DEFAULT_SCHEMA=[dbo]
GO
/****** Object:  User [BABO\학생]    Script Date: 10/29/2018 19:50:19 ******/
CREATE USER [BABO\학생] WITH DEFAULT_SCHEMA=[dbo]
GO
/****** Object:  Table [dbo].[ITEM_CATEGORY]    Script Date: 10/29/2018 19:50:20 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[ITEM_CATEGORY](
	[categoryNum] [int] NOT NULL,
	[categoryName] [nchar](10) NOT NULL,
 CONSTRAINT [PK__ITEM_CATEGORY] PRIMARY KEY CLUSTERED 
(
	[categoryNum] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
INSERT [dbo].[ITEM_CATEGORY] ([categoryNum], [categoryName]) VALUES (10000, N'OBJECT    ')
INSERT [dbo].[ITEM_CATEGORY] ([categoryNum], [categoryName]) VALUES (30000, N'THEME     ')
INSERT [dbo].[ITEM_CATEGORY] ([categoryNum], [categoryName]) VALUES (40000, N'HEAD      ')
INSERT [dbo].[ITEM_CATEGORY] ([categoryNum], [categoryName]) VALUES (50000, N'COLOR     ')
INSERT [dbo].[ITEM_CATEGORY] ([categoryNum], [categoryName]) VALUES (60000, N'BODY      ')
INSERT [dbo].[ITEM_CATEGORY] ([categoryNum], [categoryName]) VALUES (70000, N'TYPE      ')
INSERT [dbo].[ITEM_CATEGORY] ([categoryNum], [categoryName]) VALUES (80000, N'TERRAIN   ')
/****** Object:  Table [dbo].[ACCOUNT]    Script Date: 10/29/2018 19:50:20 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[ACCOUNT](
	[id] [nchar](10) NOT NULL,
	[pw] [nchar](10) NOT NULL,
	[personName] [nchar](10) NOT NULL,
	[personId] [nchar](14) NOT NULL,
	[eMail] [nchar](30) NOT NULL,
	[accountCreate] [smalldatetime] NOT NULL,
	[loginTime] [smalldatetime] NULL,
	[logoutTime] [smalldatetime] NULL,
 CONSTRAINT [PK__ACCOUNT] PRIMARY KEY CLUSTERED 
(
	[id] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY],
 CONSTRAINT [UQ__ACCOUNT_personId] UNIQUE NONCLUSTERED 
(
	[personId] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
INSERT [dbo].[ACCOUNT] ([id], [pw], [personName], [personId], [eMail], [accountCreate], [loginTime], [logoutTime]) VALUES (N'000000    ', N'000000    ', N'000000    ', N'000000        ', N'000000                        ', CAST(0x9C550371 AS SmallDateTime), CAST(0x9C550380 AS SmallDateTime), NULL)
INSERT [dbo].[ACCOUNT] ([id], [pw], [personName], [personId], [eMail], [accountCreate], [loginTime], [logoutTime]) VALUES (N'090       ', N'090       ', N'090       ', N'090           ', N'090                           ', CAST(0x9C5E0371 AS SmallDateTime), CAST(0x9C5E0371 AS SmallDateTime), NULL)
INSERT [dbo].[ACCOUNT] ([id], [pw], [personName], [personId], [eMail], [accountCreate], [loginTime], [logoutTime]) VALUES (N'1         ', N'1         ', N'1         ', N'2             ', N'1                             ', CAST(0x9C650062 AS SmallDateTime), CAST(0x9C650062 AS SmallDateTime), NULL)
INSERT [dbo].[ACCOUNT] ([id], [pw], [personName], [personId], [eMail], [accountCreate], [loginTime], [logoutTime]) VALUES (N'101010    ', N'101010    ', N'101010    ', N'101010        ', N'111111                        ', CAST(0x9C50035E AS SmallDateTime), CAST(0x9C500367 AS SmallDateTime), NULL)
INSERT [dbo].[ACCOUNT] ([id], [pw], [personName], [personId], [eMail], [accountCreate], [loginTime], [logoutTime]) VALUES (N'111       ', N'111       ', N'11        ', N'000           ', N'11                            ', CAST(0x9C4E03D2 AS SmallDateTime), CAST(0x9C5403D2 AS SmallDateTime), NULL)
INSERT [dbo].[ACCOUNT] ([id], [pw], [personName], [personId], [eMail], [accountCreate], [loginTime], [logoutTime]) VALUES (N'1122333   ', N'1234      ', N'1234      ', N'1234          ', N'1234                          ', CAST(0x9C50034D AS SmallDateTime), CAST(0x9C50034E AS SmallDateTime), NULL)
INSERT [dbo].[ACCOUNT] ([id], [pw], [personName], [personId], [eMail], [accountCreate], [loginTime], [logoutTime]) VALUES (N'1233      ', N'1233      ', N'1233      ', N'1233          ', N'1233                          ', CAST(0x9CA202DC AS SmallDateTime), CAST(0x9CA202DE AS SmallDateTime), NULL)
INSERT [dbo].[ACCOUNT] ([id], [pw], [personName], [personId], [eMail], [accountCreate], [loginTime], [logoutTime]) VALUES (N'1234      ', N'1234      ', N'1234      ', N'12344         ', N'1234                          ', CAST(0x9C5003FD AS SmallDateTime), CAST(0x9C5003FD AS SmallDateTime), NULL)
INSERT [dbo].[ACCOUNT] ([id], [pw], [personName], [personId], [eMail], [accountCreate], [loginTime], [logoutTime]) VALUES (N'12345     ', N'12345     ', N'sdf       ', N'343423        ', N'5435                          ', CAST(0x9C4C03E4 AS SmallDateTime), CAST(0x9C4C03E4 AS SmallDateTime), NULL)
INSERT [dbo].[ACCOUNT] ([id], [pw], [personName], [personId], [eMail], [accountCreate], [loginTime], [logoutTime]) VALUES (N'123456    ', N'1234      ', N'lee       ', N'7709291661816 ', N'catsis2@cj.net                ', CAST(0x9C500337 AS SmallDateTime), CAST(0x9C500339 AS SmallDateTime), NULL)
INSERT [dbo].[ACCOUNT] ([id], [pw], [personName], [personId], [eMail], [accountCreate], [loginTime], [logoutTime]) VALUES (N'2462      ', N'1234      ', N'aa        ', N'999           ', N'1                             ', CAST(0x9C440346 AS SmallDateTime), CAST(0x9C440347 AS SmallDateTime), NULL)
INSERT [dbo].[ACCOUNT] ([id], [pw], [personName], [personId], [eMail], [accountCreate], [loginTime], [logoutTime]) VALUES (N'6666      ', N'6666      ', N'6666      ', N'6666          ', N'6666                          ', CAST(0x9C4E005C AS SmallDateTime), CAST(0x9C4E005C AS SmallDateTime), NULL)
INSERT [dbo].[ACCOUNT] ([id], [pw], [personName], [personId], [eMail], [accountCreate], [loginTime], [logoutTime]) VALUES (N'666666    ', N'666666    ', N'666666    ', N'666666        ', N'666666                        ', CAST(0x9C4C04E2 AS SmallDateTime), CAST(0x9C4C04E2 AS SmallDateTime), NULL)
INSERT [dbo].[ACCOUNT] ([id], [pw], [personName], [personId], [eMail], [accountCreate], [loginTime], [logoutTime]) VALUES (N'66667     ', N'66667     ', N'66667     ', N'66667         ', N'66667                         ', CAST(0x9C5502FB AS SmallDateTime), CAST(0x9C5502FB AS SmallDateTime), NULL)
INSERT [dbo].[ACCOUNT] ([id], [pw], [personName], [personId], [eMail], [accountCreate], [loginTime], [logoutTime]) VALUES (N'777       ', N'777       ', N'777       ', N'777           ', N'777                           ', CAST(0x9C4E009F AS SmallDateTime), CAST(0x9C4E00A0 AS SmallDateTime), NULL)
INSERT [dbo].[ACCOUNT] ([id], [pw], [personName], [personId], [eMail], [accountCreate], [loginTime], [logoutTime]) VALUES (N'77777     ', N'777       ', N'777       ', N'77777         ', N'777                           ', CAST(0x9C500275 AS SmallDateTime), CAST(0x9C5002DF AS SmallDateTime), NULL)
INSERT [dbo].[ACCOUNT] ([id], [pw], [personName], [personId], [eMail], [accountCreate], [loginTime], [logoutTime]) VALUES (N'909090    ', N'909090    ', N'999       ', N'99999         ', N'9999                          ', CAST(0x9C5002E0 AS SmallDateTime), CAST(0x9C5002E0 AS SmallDateTime), NULL)
INSERT [dbo].[ACCOUNT] ([id], [pw], [personName], [personId], [eMail], [accountCreate], [loginTime], [logoutTime]) VALUES (N'가나다       ', N'2345      ', N'해해        ', N'820912-123456 ', N'가나다@가나다.com                   ', CAST(0x9C500287 AS SmallDateTime), CAST(0x9C500288 AS SmallDateTime), NULL)
INSERT [dbo].[ACCOUNT] ([id], [pw], [personName], [personId], [eMail], [accountCreate], [loginTime], [logoutTime]) VALUES (N'안아줘승연아    ', N'1101      ', N'전현준       ', N'8888888888888 ', N'tgcv@naver.com                ', CAST(0x9C6102B2 AS SmallDateTime), CAST(0x9C6102E6 AS SmallDateTime), NULL)
INSERT [dbo].[ACCOUNT] ([id], [pw], [personName], [personId], [eMail], [accountCreate], [loginTime], [logoutTime]) VALUES (N'엔ㅋ진ㅋ      ', N'1111      ', N'동ㅋ석ㅋ      ', N'1111          ', N'1111                          ', CAST(0x9C410195 AS SmallDateTime), CAST(0x9C4D03ED AS SmallDateTime), NULL)
INSERT [dbo].[ACCOUNT] ([id], [pw], [personName], [personId], [eMail], [accountCreate], [loginTime], [logoutTime]) VALUES (N'제라드       ', N'12345     ', N'제라드       ', N'12            ', N'1                             ', CAST(0x9C4302E6 AS SmallDateTime), CAST(0x9C500295 AS SmallDateTime), NULL)
INSERT [dbo].[ACCOUNT] ([id], [pw], [personName], [personId], [eMail], [accountCreate], [loginTime], [logoutTime]) VALUES (N'코만도스      ', N'파인코만      ', N'그린베레      ', N'18181818      ', N'123123                        ', CAST(0x9C410188 AS SmallDateTime), CAST(0x9C4101D8 AS SmallDateTime), NULL)
INSERT [dbo].[ACCOUNT] ([id], [pw], [personName], [personId], [eMail], [accountCreate], [loginTime], [logoutTime]) VALUES (N'휘플휘플      ', N'1         ', N'김시현       ', N'00000         ', N'1111                          ', CAST(0x9C500459 AS SmallDateTime), CAST(0x9C50045D AS SmallDateTime), NULL)
INSERT [dbo].[ACCOUNT] ([id], [pw], [personName], [personId], [eMail], [accountCreate], [loginTime], [logoutTime]) VALUES (N'a         ', N'a         ', N'오스트랄로피테쿠스 ', N'12222         ', N'12222                         ', CAST(0x9C4D03AE AS SmallDateTime), CAST(0x9C62030F AS SmallDateTime), NULL)
INSERT [dbo].[ACCOUNT] ([id], [pw], [personName], [personId], [eMail], [accountCreate], [loginTime], [logoutTime]) VALUES (N'a1234     ', N'12345     ', N'dddd      ', N'11111111111   ', N'2222                          ', CAST(0x9C5002F2 AS SmallDateTime), CAST(0x9C5002F3 AS SmallDateTime), NULL)
INSERT [dbo].[ACCOUNT] ([id], [pw], [personName], [personId], [eMail], [accountCreate], [loginTime], [logoutTime]) VALUES (N'aa        ', N'aa        ', N'aa        ', N'aa            ', N'aa                            ', CAST(0x9C50034C AS SmallDateTime), CAST(0x9C50034C AS SmallDateTime), NULL)
INSERT [dbo].[ACCOUNT] ([id], [pw], [personName], [personId], [eMail], [accountCreate], [loginTime], [logoutTime]) VALUES (N'aaa       ', N'1234      ', N'ㅁㄴㅇ       ', N'11            ', N'11                            ', CAST(0x9C410323 AS SmallDateTime), CAST(0x9C820500 AS SmallDateTime), NULL)
INSERT [dbo].[ACCOUNT] ([id], [pw], [personName], [personId], [eMail], [accountCreate], [loginTime], [logoutTime]) VALUES (N'aaaa      ', N'aaaa      ', N'aaa       ', N'121           ', N'121                           ', CAST(0x9C5002D6 AS SmallDateTime), CAST(0x9C5002D6 AS SmallDateTime), NULL)
INSERT [dbo].[ACCOUNT] ([id], [pw], [personName], [personId], [eMail], [accountCreate], [loginTime], [logoutTime]) VALUES (N'aaaaa     ', N'dfd       ', N'dfd       ', N'dfd           ', N'dfd                           ', CAST(0x9C51054E AS SmallDateTime), CAST(0x9C510550 AS SmallDateTime), NULL)
INSERT [dbo].[ACCOUNT] ([id], [pw], [personName], [personId], [eMail], [accountCreate], [loginTime], [logoutTime]) VALUES (N'aaad      ', N'aaa       ', N'1wer      ', N'adf           ', N'afd                           ', CAST(0x9C50043E AS SmallDateTime), CAST(0x9C50043E AS SmallDateTime), NULL)
INSERT [dbo].[ACCOUNT] ([id], [pw], [personName], [personId], [eMail], [accountCreate], [loginTime], [logoutTime]) VALUES (N'ab123     ', N'aaaaa     ', N'aaa       ', N'11111         ', N'aaaa                          ', CAST(0x9C500325 AS SmallDateTime), CAST(0x9C500326 AS SmallDateTime), NULL)
INSERT [dbo].[ACCOUNT] ([id], [pw], [personName], [personId], [eMail], [accountCreate], [loginTime], [logoutTime]) VALUES (N'abcdef    ', N'abcdef    ', N'강태        ', N'3434          ', N'234324                        ', CAST(0x9C450364 AS SmallDateTime), CAST(0x9C450364 AS SmallDateTime), NULL)
INSERT [dbo].[ACCOUNT] ([id], [pw], [personName], [personId], [eMail], [accountCreate], [loginTime], [logoutTime]) VALUES (N'abcdsp    ', N'1234      ', N'fdasfdaf  ', N'1111111111111 ', N'dsafafdsf                     ', CAST(0x9C5003CD AS SmallDateTime), CAST(0x9C5003CD AS SmallDateTime), NULL)
INSERT [dbo].[ACCOUNT] ([id], [pw], [personName], [personId], [eMail], [accountCreate], [loginTime], [logoutTime]) VALUES (N'as        ', N'as        ', N'af        ', N'af            ', N'af                            ', CAST(0x9C5604A1 AS SmallDateTime), CAST(0x9C5604A1 AS SmallDateTime), NULL)
INSERT [dbo].[ACCOUNT] ([id], [pw], [personName], [personId], [eMail], [accountCreate], [loginTime], [logoutTime]) VALUES (N'asdasd    ', N'asdasd    ', N'asdasd    ', N'asdasd        ', N'asdasd                        ', CAST(0x9C3C0320 AS SmallDateTime), CAST(0x9C4E0440 AS SmallDateTime), NULL)
INSERT [dbo].[ACCOUNT] ([id], [pw], [personName], [personId], [eMail], [accountCreate], [loginTime], [logoutTime]) VALUES (N'asdd      ', N'asdd      ', N'asdd      ', N'1231233       ', N'1231233                       ', CAST(0x9CA202E1 AS SmallDateTime), CAST(0x9CA202E1 AS SmallDateTime), NULL)
INSERT [dbo].[ACCOUNT] ([id], [pw], [personName], [personId], [eMail], [accountCreate], [loginTime], [logoutTime]) VALUES (N'b4paper   ', N'great1    ', N'이석원       ', N'00            ', N'0000                          ', CAST(0x9C50052E AS SmallDateTime), CAST(0x9C500530 AS SmallDateTime), NULL)
INSERT [dbo].[ACCOUNT] ([id], [pw], [personName], [personId], [eMail], [accountCreate], [loginTime], [logoutTime]) VALUES (N'besoul    ', N'820212    ', N'이창규       ', N'828228282828  ', N'ㄷㅈㄹㅈㄹㄹ                        ', CAST(0x9C500414 AS SmallDateTime), CAST(0x9C500415 AS SmallDateTime), NULL)
INSERT [dbo].[ACCOUNT] ([id], [pw], [personName], [personId], [eMail], [accountCreate], [loginTime], [logoutTime]) VALUES (N'bublapse  ', N'0503l     ', N'kihs      ', N'9874659462457 ', N'df@df.d                       ', CAST(0x9C50030D AS SmallDateTime), CAST(0x9C50046E AS SmallDateTime), NULL)
INSERT [dbo].[ACCOUNT] ([id], [pw], [personName], [personId], [eMail], [accountCreate], [loginTime], [logoutTime]) VALUES (N'carobe    ', N'1209      ', N'sam       ', N'8612090000000 ', N'carobe@naver.com              ', CAST(0x9C5504DB AS SmallDateTime), CAST(0x9C5504DB AS SmallDateTime), NULL)
INSERT [dbo].[ACCOUNT] ([id], [pw], [personName], [personId], [eMail], [accountCreate], [loginTime], [logoutTime]) VALUES (N'chaen     ', N'1111      ', N'aaa       ', N'3070          ', N'1111                          ', CAST(0x9C5004AA AS SmallDateTime), CAST(0x9C5004AD AS SmallDateTime), NULL)
INSERT [dbo].[ACCOUNT] ([id], [pw], [personName], [personId], [eMail], [accountCreate], [loginTime], [logoutTime]) VALUES (N'clous02   ', N'rmawls    ', N'황성현       ', N'8503061058915 ', N'clous02@naver.com             ', CAST(0x9C500379 AS SmallDateTime), CAST(0x9C50037A AS SmallDateTime), NULL)
INSERT [dbo].[ACCOUNT] ([id], [pw], [personName], [personId], [eMail], [accountCreate], [loginTime], [logoutTime]) VALUES (N'crishna   ', N'1234      ', N'1111      ', N'111111111111  ', N'1111                          ', CAST(0x9C50045C AS SmallDateTime), CAST(0x9C50045F AS SmallDateTime), NULL)
INSERT [dbo].[ACCOUNT] ([id], [pw], [personName], [personId], [eMail], [accountCreate], [loginTime], [logoutTime]) VALUES (N'dev3t173  ', N'1111      ', N'이재홍       ', N'8604231111111 ', N'pleiades04@naver.com          ', CAST(0x9C4F03E2 AS SmallDateTime), CAST(0x9C4F0515 AS SmallDateTime), NULL)
INSERT [dbo].[ACCOUNT] ([id], [pw], [personName], [personId], [eMail], [accountCreate], [loginTime], [logoutTime]) VALUES (N'dfd       ', N'fdf       ', N'fdf       ', N'fdf           ', N'fdf                           ', CAST(0x9C51054E AS SmallDateTime), NULL, NULL)
INSERT [dbo].[ACCOUNT] ([id], [pw], [personName], [personId], [eMail], [accountCreate], [loginTime], [logoutTime]) VALUES (N'dfg       ', N'dfg       ', N'dfg       ', N'dfg           ', N'dfg                           ', CAST(0x9C4002CA AS SmallDateTime), CAST(0x9C5B046B AS SmallDateTime), NULL)
INSERT [dbo].[ACCOUNT] ([id], [pw], [personName], [personId], [eMail], [accountCreate], [loginTime], [logoutTime]) VALUES (N'eedd      ', N'eedd      ', N'a         ', N'a             ', N'a                             ', CAST(0x9C5003B9 AS SmallDateTime), CAST(0x9C5003E3 AS SmallDateTime), NULL)
INSERT [dbo].[ACCOUNT] ([id], [pw], [personName], [personId], [eMail], [accountCreate], [loginTime], [logoutTime]) VALUES (N'exa       ', N'exa       ', N'exa       ', N'exa           ', N'exa                           ', CAST(0x9C3F0355 AS SmallDateTime), CAST(0x9C4F02E7 AS SmallDateTime), NULL)
INSERT [dbo].[ACCOUNT] ([id], [pw], [personName], [personId], [eMail], [accountCreate], [loginTime], [logoutTime]) VALUES (N'exxa      ', N'exxa      ', N'exxa      ', N'exxa          ', N'exxa                          ', CAST(0x9C3C0504 AS SmallDateTime), CAST(0x9C820501 AS SmallDateTime), NULL)
INSERT [dbo].[ACCOUNT] ([id], [pw], [personName], [personId], [eMail], [accountCreate], [loginTime], [logoutTime]) VALUES (N'flybird   ', N'1021109   ', N'임         ', N'123456789     ', N'flyb@naver.com                ', CAST(0x9C5003CD AS SmallDateTime), CAST(0x9C5003CD AS SmallDateTime), NULL)
INSERT [dbo].[ACCOUNT] ([id], [pw], [personName], [personId], [eMail], [accountCreate], [loginTime], [logoutTime]) VALUES (N'gggg      ', N'GGGG      ', N'GGGG      ', N'2323423423    ', N'WEGWEG                        ', CAST(0x9C50030C AS SmallDateTime), CAST(0x9C50030C AS SmallDateTime), NULL)
INSERT [dbo].[ACCOUNT] ([id], [pw], [personName], [personId], [eMail], [accountCreate], [loginTime], [logoutTime]) VALUES (N'gihanim   ', N'1212      ', N'기하        ', N'8400000000000 ', N'ksdfasdfd@hotmail.com         ', CAST(0x9C500434 AS SmallDateTime), CAST(0x9C50056B AS SmallDateTime), NULL)
INSERT [dbo].[ACCOUNT] ([id], [pw], [personName], [personId], [eMail], [accountCreate], [loginTime], [logoutTime]) VALUES (N'gu1       ', N'gu1       ', N'123123123 ', N'123123        ', N'123123                        ', CAST(0x9C50031A AS SmallDateTime), CAST(0x9C500327 AS SmallDateTime), NULL)
INSERT [dbo].[ACCOUNT] ([id], [pw], [personName], [personId], [eMail], [accountCreate], [loginTime], [logoutTime]) VALUES (N'gu9gu9    ', N'gu9gu9    ', N'gu9gu9    ', N'gu9g9u        ', N'gu9gu9                        ', CAST(0x9C50030A AS SmallDateTime), NULL, NULL)
INSERT [dbo].[ACCOUNT] ([id], [pw], [personName], [personId], [eMail], [accountCreate], [loginTime], [logoutTime]) VALUES (N'gugu      ', N'gugu      ', N'gugu      ', N'gugu          ', N'gugu                          ', CAST(0x9C3C0532 AS SmallDateTime), CAST(0x9C6501C2 AS SmallDateTime), NULL)
INSERT [dbo].[ACCOUNT] ([id], [pw], [personName], [personId], [eMail], [accountCreate], [loginTime], [logoutTime]) VALUES (N'gugu8     ', N'gugu8     ', N'gugu8     ', N'1234567890123 ', N'qwe                           ', CAST(0x9C4904ED AS SmallDateTime), NULL, NULL)
INSERT [dbo].[ACCOUNT] ([id], [pw], [personName], [personId], [eMail], [accountCreate], [loginTime], [logoutTime]) VALUES (N'iii       ', N'iii       ', N'iii       ', N'iii           ', N'iii                           ', CAST(0x9C6E0407 AS SmallDateTime), CAST(0x9C6E0408 AS SmallDateTime), NULL)
INSERT [dbo].[ACCOUNT] ([id], [pw], [personName], [personId], [eMail], [accountCreate], [loginTime], [logoutTime]) VALUES (N'junios    ', N'1234      ', N'Junios    ', N'111111111     ', N'junios@empal.com              ', CAST(0x9C500321 AS SmallDateTime), CAST(0x9C500321 AS SmallDateTime), NULL)
INSERT [dbo].[ACCOUNT] ([id], [pw], [personName], [personId], [eMail], [accountCreate], [loginTime], [logoutTime]) VALUES (N'kallru    ', N'1234      ', N'kall      ', N'8654751236578 ', N'11                            ', CAST(0x9C50049C AS SmallDateTime), CAST(0x9C50049C AS SmallDateTime), NULL)
INSERT [dbo].[ACCOUNT] ([id], [pw], [personName], [personId], [eMail], [accountCreate], [loginTime], [logoutTime]) VALUES (N'kgda      ', N'1111      ', N'kgda      ', N'1111111111118 ', N'111@111.111                   ', CAST(0x9C73023F AS SmallDateTime), CAST(0x9C940077 AS SmallDateTime), NULL)
INSERT [dbo].[ACCOUNT] ([id], [pw], [personName], [personId], [eMail], [accountCreate], [loginTime], [logoutTime]) VALUES (N'kkh       ', N'1004      ', N'강국헌       ', N'831105192161  ', N'kk831105                      ', CAST(0x9C410189 AS SmallDateTime), CAST(0x9C990587 AS SmallDateTime), NULL)
INSERT [dbo].[ACCOUNT] ([id], [pw], [personName], [personId], [eMail], [accountCreate], [loginTime], [logoutTime]) VALUES (N'kokoro    ', N'1234      ', N'kokoro    ', N'123           ', N'123                           ', CAST(0x9C50031A AS SmallDateTime), CAST(0x9C50031A AS SmallDateTime), NULL)
INSERT [dbo].[ACCOUNT] ([id], [pw], [personName], [personId], [eMail], [accountCreate], [loginTime], [logoutTime]) VALUES (N'ktandya   ', N'1010      ', N'클스        ', N'3644765876987 ', N'ㅓㅗ                            ', CAST(0x9C7C042B AS SmallDateTime), CAST(0x9C7C0433 AS SmallDateTime), NULL)
INSERT [dbo].[ACCOUNT] ([id], [pw], [personName], [personId], [eMail], [accountCreate], [loginTime], [logoutTime]) VALUES (N'lancekun  ', N'123       ', N'황동윤       ', N'시로링           ', N'23@23                         ', CAST(0x9C610320 AS SmallDateTime), CAST(0x9C610320 AS SmallDateTime), NULL)
INSERT [dbo].[ACCOUNT] ([id], [pw], [personName], [personId], [eMail], [accountCreate], [loginTime], [logoutTime]) VALUES (N'lightdark ', N'1234qwer  ', N'우상재       ', N'12=3\         ', N'1234                          ', CAST(0x9C50045D AS SmallDateTime), CAST(0x9C50045D AS SmallDateTime), NULL)
INSERT [dbo].[ACCOUNT] ([id], [pw], [personName], [personId], [eMail], [accountCreate], [loginTime], [logoutTime]) VALUES (N'mook      ', N'1234      ', N'상묵        ', N'123141234     ', N'asdf@asdf.com                 ', CAST(0x9C5002E4 AS SmallDateTime), CAST(0x9C5002E6 AS SmallDateTime), NULL)
INSERT [dbo].[ACCOUNT] ([id], [pw], [personName], [personId], [eMail], [accountCreate], [loginTime], [logoutTime]) VALUES (N'naganola  ', N'24680     ', N'asdf      ', N'12345678      ', N'asdf@hotmail.com              ', CAST(0x9C610015 AS SmallDateTime), NULL, NULL)
INSERT [dbo].[ACCOUNT] ([id], [pw], [personName], [personId], [eMail], [accountCreate], [loginTime], [logoutTime]) VALUES (N'ppp       ', N'ppp       ', N'ppp       ', N'ppp           ', N'ppp                           ', CAST(0x9C6B02F1 AS SmallDateTime), CAST(0x9C6B02F5 AS SmallDateTime), NULL)
INSERT [dbo].[ACCOUNT] ([id], [pw], [personName], [personId], [eMail], [accountCreate], [loginTime], [logoutTime]) VALUES (N'pppp      ', N'pppp      ', N'pppp      ', N'pppp          ', N'pppp                          ', CAST(0x9C6C0245 AS SmallDateTime), CAST(0x9C6C0245 AS SmallDateTime), NULL)
INSERT [dbo].[ACCOUNT] ([id], [pw], [personName], [personId], [eMail], [accountCreate], [loginTime], [logoutTime]) VALUES (N'ppppp     ', N'ppppp     ', N'ppppp     ', N'ppppp         ', N'ppppp                         ', CAST(0x9C6D03C9 AS SmallDateTime), CAST(0x9C6D03C9 AS SmallDateTime), NULL)
INSERT [dbo].[ACCOUNT] ([id], [pw], [personName], [personId], [eMail], [accountCreate], [loginTime], [logoutTime]) VALUES (N'qook      ', N'Qook      ', N'qq        ', N'qq            ', N'qq                            ', CAST(0x9C3D0486 AS SmallDateTime), CAST(0x9C3D04D0 AS SmallDateTime), NULL)
INSERT [dbo].[ACCOUNT] ([id], [pw], [personName], [personId], [eMail], [accountCreate], [loginTime], [logoutTime]) VALUES (N'qqq       ', N'qqq       ', N'qqq       ', N'qqq           ', N'qqq                           ', CAST(0x9C3F0305 AS SmallDateTime), CAST(0x9C3F0525 AS SmallDateTime), NULL)
INSERT [dbo].[ACCOUNT] ([id], [pw], [personName], [personId], [eMail], [accountCreate], [loginTime], [logoutTime]) VALUES (N'qwer      ', N'qwer      ', N'qwer      ', N'qwer          ', N'qwer                          ', CAST(0x9C410322 AS SmallDateTime), CAST(0x9C990587 AS SmallDateTime), NULL)
INSERT [dbo].[ACCOUNT] ([id], [pw], [personName], [personId], [eMail], [accountCreate], [loginTime], [logoutTime]) VALUES (N'qwerasdf  ', N'qwerasdf  ', N'qwer      ', N'qwerasdf      ', N'qwer                          ', CAST(0x9C55026C AS SmallDateTime), CAST(0x9C5502FA AS SmallDateTime), NULL)
INSERT [dbo].[ACCOUNT] ([id], [pw], [personName], [personId], [eMail], [accountCreate], [loginTime], [logoutTime]) VALUES (N'riot0083  ', N'1234      ', N'1234      ', N'67767567      ', N'1234                          ', CAST(0x9C50042C AS SmallDateTime), CAST(0x9C50042E AS SmallDateTime), NULL)
INSERT [dbo].[ACCOUNT] ([id], [pw], [personName], [personId], [eMail], [accountCreate], [loginTime], [logoutTime]) VALUES (N'rkskekfk  ', N'rkskekfk  ', N'dfdf      ', N'86456         ', N'3434                          ', CAST(0x9C440401 AS SmallDateTime), CAST(0x9C440404 AS SmallDateTime), NULL)
INSERT [dbo].[ACCOUNT] ([id], [pw], [personName], [personId], [eMail], [accountCreate], [loginTime], [logoutTime]) VALUES (N'saqwe     ', N'1         ', N'재혁        ', N'1             ', N'12                            ', CAST(0x9C3D03B8 AS SmallDateTime), CAST(0x9C680023 AS SmallDateTime), NULL)
INSERT [dbo].[ACCOUNT] ([id], [pw], [personName], [personId], [eMail], [accountCreate], [loginTime], [logoutTime]) VALUES (N'sdf       ', N'sdf       ', N'sdf       ', N'sdf           ', N'sdf                           ', CAST(0x9C3C0521 AS SmallDateTime), CAST(0x9C4002C1 AS SmallDateTime), NULL)
INSERT [dbo].[ACCOUNT] ([id], [pw], [personName], [personId], [eMail], [accountCreate], [loginTime], [logoutTime]) VALUES (N'sp        ', N'sp        ', N'sp        ', N'sp            ', N'sp                            ', CAST(0x9C3F02EC AS SmallDateTime), CAST(0x9C3F02FF AS SmallDateTime), NULL)
INSERT [dbo].[ACCOUNT] ([id], [pw], [personName], [personId], [eMail], [accountCreate], [loginTime], [logoutTime]) VALUES (N'test1     ', N'test1     ', N'test1     ', N'test1         ', N'test1                         ', CAST(0x9C3D0345 AS SmallDateTime), CAST(0x9C62029B AS SmallDateTime), NULL)
INSERT [dbo].[ACCOUNT] ([id], [pw], [personName], [personId], [eMail], [accountCreate], [loginTime], [logoutTime]) VALUES (N'test2     ', N'test2     ', N'test2     ', N'test2         ', N'test2                         ', CAST(0x9C3D0346 AS SmallDateTime), CAST(0x9C4F0314 AS SmallDateTime), NULL)
INSERT [dbo].[ACCOUNT] ([id], [pw], [personName], [personId], [eMail], [accountCreate], [loginTime], [logoutTime]) VALUES (N'test3     ', N'test3     ', N'test3     ', N'test3         ', N'test3                         ', CAST(0x9C4E03AA AS SmallDateTime), CAST(0x9C4E03AA AS SmallDateTime), NULL)
INSERT [dbo].[ACCOUNT] ([id], [pw], [personName], [personId], [eMail], [accountCreate], [loginTime], [logoutTime]) VALUES (N'viceboss  ', N'dmgpgp    ', N'허재민       ', N'111111        ', N'1111                          ', CAST(0x9C50033B AS SmallDateTime), CAST(0x9C500342 AS SmallDateTime), NULL)
INSERT [dbo].[ACCOUNT] ([id], [pw], [personName], [personId], [eMail], [accountCreate], [loginTime], [logoutTime]) VALUES (N'wer       ', N'wer       ', N'wer       ', N'wer           ', N'wer                           ', CAST(0x9C4002C7 AS SmallDateTime), CAST(0x9C6304CE AS SmallDateTime), NULL)
INSERT [dbo].[ACCOUNT] ([id], [pw], [personName], [personId], [eMail], [accountCreate], [loginTime], [logoutTime]) VALUES (N'wow       ', N'wow       ', N'wow       ', N'wow           ', N'wow                           ', CAST(0x9C46038B AS SmallDateTime), CAST(0x9C6501C2 AS SmallDateTime), NULL)
INSERT [dbo].[ACCOUNT] ([id], [pw], [personName], [personId], [eMail], [accountCreate], [loginTime], [logoutTime]) VALUES (N'wp        ', N'wp        ', N'wp        ', N'wp            ', N'wp                            ', CAST(0x9C410195 AS SmallDateTime), CAST(0x9C62030F AS SmallDateTime), NULL)
INSERT [dbo].[ACCOUNT] ([id], [pw], [personName], [personId], [eMail], [accountCreate], [loginTime], [logoutTime]) VALUES (N'xcv       ', N'xcv       ', N'xcv       ', N'xcv           ', N'xcv                           ', CAST(0x9C4002D1 AS SmallDateTime), CAST(0x9C40038E AS SmallDateTime), NULL)
INSERT [dbo].[ACCOUNT] ([id], [pw], [personName], [personId], [eMail], [accountCreate], [loginTime], [logoutTime]) VALUES (N'xwvvwx    ', N'x13579x   ', N'jik2019   ', N'92762897      ', N'asfsf@asfe.com                ', CAST(0x9C520328 AS SmallDateTime), CAST(0x9C52032B AS SmallDateTime), NULL)
INSERT [dbo].[ACCOUNT] ([id], [pw], [personName], [personId], [eMail], [accountCreate], [loginTime], [logoutTime]) VALUES (N'zzz       ', N'zzz       ', N'zzz       ', N'zzz           ', N'zzz                           ', CAST(0x9C3F02CF AS SmallDateTime), CAST(0x9C4101D3 AS SmallDateTime), NULL)
INSERT [dbo].[ACCOUNT] ([id], [pw], [personName], [personId], [eMail], [accountCreate], [loginTime], [logoutTime]) VALUES (N'zzzz      ', N'zzzz      ', N'zzzz      ', N'zzzz          ', N'zzzz                          ', CAST(0x9C410186 AS SmallDateTime), CAST(0x9C410186 AS SmallDateTime), NULL)
/****** Object:  Table [dbo].[DEAL_MODE]    Script Date: 10/29/2018 19:50:20 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[DEAL_MODE](
	[dealMode] [tinyint] NOT NULL,
	[dealStr] [nchar](10) NOT NULL,
 CONSTRAINT [PK__DEAL_MODE] PRIMARY KEY CLUSTERED 
(
	[dealMode] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
INSERT [dbo].[DEAL_MODE] ([dealMode], [dealStr]) VALUES (0, N'기본지급      ')
INSERT [dbo].[DEAL_MODE] ([dealMode], [dealStr]) VALUES (1, N'상점구매      ')
INSERT [dbo].[DEAL_MODE] ([dealMode], [dealStr]) VALUES (2, N'상점판매      ')
/****** Object:  Table [dbo].[CHARACTER_BASE]    Script Date: 10/29/2018 19:50:20 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[CHARACTER_BASE](
	[characterName] [nchar](10) NOT NULL,
	[id] [nchar](10) NOT NULL,
	[exper] [int] NOT NULL,
	[gameMoney] [int] NOT NULL,
	[starMoney] [int] NOT NULL,
	[risingStar] [int] NOT NULL,
	[birthday] [smalldatetime] NOT NULL,
 CONSTRAINT [PK__CHARACTER_BASE] PRIMARY KEY CLUSTERED 
(
	[characterName] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
INSERT [dbo].[CHARACTER_BASE] ([characterName], [id], [exper], [gameMoney], [starMoney], [risingStar], [birthday]) VALUES (N'1         ', N'1         ', 0, 10000, 100, 100, CAST(0x9C650062 AS SmallDateTime))
INSERT [dbo].[CHARACTER_BASE] ([characterName], [id], [exper], [gameMoney], [starMoney], [risingStar], [birthday]) VALUES (N'5555      ', N'1234      ', 0, 10000, 100, 100, CAST(0x9C5003FD AS SmallDateTime))
INSERT [dbo].[CHARACTER_BASE] ([characterName], [id], [exper], [gameMoney], [starMoney], [risingStar], [birthday]) VALUES (N'666       ', N'b4paper   ', 0, 3000, 180, 0, CAST(0x9C50052E AS SmallDateTime))
INSERT [dbo].[CHARACTER_BASE] ([characterName], [id], [exper], [gameMoney], [starMoney], [risingStar], [birthday]) VALUES (N'777       ', N'777       ', 0, 0, 0, 0, CAST(0x9C4E009F AS SmallDateTime))
INSERT [dbo].[CHARACTER_BASE] ([characterName], [id], [exper], [gameMoney], [starMoney], [risingStar], [birthday]) VALUES (N'가오리       ', N'1122333   ', 0, 10000, 100, 100, CAST(0x9C50034D AS SmallDateTime))
INSERT [dbo].[CHARACTER_BASE] ([characterName], [id], [exper], [gameMoney], [starMoney], [risingStar], [birthday]) VALUES (N'곰발바닥      ', N'Qook      ', 100000, 1000000, 1000000, 1000000, CAST(0x9C3D0486 AS SmallDateTime))
INSERT [dbo].[CHARACTER_BASE] ([characterName], [id], [exper], [gameMoney], [starMoney], [risingStar], [birthday]) VALUES (N'공구함       ', N'123456    ', 2910, 5500, 100, 351, CAST(0x9C500337 AS SmallDateTime))
INSERT [dbo].[CHARACTER_BASE] ([characterName], [id], [exper], [gameMoney], [starMoney], [risingStar], [birthday]) VALUES (N'기하        ', N'gihanim   ', 2290, 3350, 217, 59, CAST(0x9C500434 AS SmallDateTime))
INSERT [dbo].[CHARACTER_BASE] ([characterName], [id], [exper], [gameMoney], [starMoney], [risingStar], [birthday]) VALUES (N'기획서용      ', N'12345     ', 0, 0, 0, 0, CAST(0x9C4C03E4 AS SmallDateTime))
INSERT [dbo].[CHARACTER_BASE] ([characterName], [id], [exper], [gameMoney], [starMoney], [risingStar], [birthday]) VALUES (N'깜빡했다      ', N'gu1       ', 2380, 10900, 100, 248, CAST(0x9C50031A AS SmallDateTime))
INSERT [dbo].[CHARACTER_BASE] ([characterName], [id], [exper], [gameMoney], [starMoney], [risingStar], [birthday]) VALUES (N'나밥줘       ', N'dev3t173  ', 2590, 4200, 100, 259, CAST(0x9C4F03E2 AS SmallDateTime))
INSERT [dbo].[CHARACTER_BASE] ([characterName], [id], [exper], [gameMoney], [starMoney], [risingStar], [birthday]) VALUES (N'님이그걸왜먹어여  ', N'a         ', 6330, 2400, 25, 413, CAST(0x9C4D03AF AS SmallDateTime))
INSERT [dbo].[CHARACTER_BASE] ([characterName], [id], [exper], [gameMoney], [starMoney], [risingStar], [birthday]) VALUES (N'다덤벼       ', N'bublapse  ', 870, 2550, 0, 137, CAST(0x9C50030D AS SmallDateTime))
INSERT [dbo].[CHARACTER_BASE] ([characterName], [id], [exper], [gameMoney], [starMoney], [risingStar], [birthday]) VALUES (N'도라에몽      ', N'clous02   ', 0, 10000, 100, 100, CAST(0x9C50037A AS SmallDateTime))
INSERT [dbo].[CHARACTER_BASE] ([characterName], [id], [exper], [gameMoney], [starMoney], [risingStar], [birthday]) VALUES (N'루나        ', N'090       ', 0, 10000, 100, 100, CAST(0x9C5E0371 AS SmallDateTime))
INSERT [dbo].[CHARACTER_BASE] ([characterName], [id], [exper], [gameMoney], [starMoney], [risingStar], [birthday]) VALUES (N'마성의유희열    ', N'sdf       ', 123456, 1000000, 1000000, 1000000, CAST(0x9C3C0521 AS SmallDateTime))
INSERT [dbo].[CHARACTER_BASE] ([characterName], [id], [exper], [gameMoney], [starMoney], [risingStar], [birthday]) VALUES (N'망크        ', N'exa       ', 43815, 1020100, 999873, 1001640, CAST(0x9C3F0355 AS SmallDateTime))
INSERT [dbo].[CHARACTER_BASE] ([characterName], [id], [exper], [gameMoney], [starMoney], [risingStar], [birthday]) VALUES (N'미순        ', N'iii       ', 0, 50, 0, 0, CAST(0x9C6E0408 AS SmallDateTime))
INSERT [dbo].[CHARACTER_BASE] ([characterName], [id], [exper], [gameMoney], [starMoney], [risingStar], [birthday]) VALUES (N'밥은먹고다니니   ', N'junios    ', 410, 50, 0, 41, CAST(0x9C500321 AS SmallDateTime))
INSERT [dbo].[CHARACTER_BASE] ([characterName], [id], [exper], [gameMoney], [starMoney], [risingStar], [birthday]) VALUES (N'별이        ', N'aaa       ', 36640, 3700, 420, 62, CAST(0x9C410323 AS SmallDateTime))
INSERT [dbo].[CHARACTER_BASE] ([characterName], [id], [exper], [gameMoney], [starMoney], [risingStar], [birthday]) VALUES (N'뽀오        ', N'crishna   ', 0, 10000, 100, 100, CAST(0x9C50045C AS SmallDateTime))
INSERT [dbo].[CHARACTER_BASE] ([characterName], [id], [exper], [gameMoney], [starMoney], [risingStar], [birthday]) VALUES (N'뿌잉        ', N'RIOT0083  ', 0, 10000, 100, 100, CAST(0x9C50042C AS SmallDateTime))
INSERT [dbo].[CHARACTER_BASE] ([characterName], [id], [exper], [gameMoney], [starMoney], [risingStar], [birthday]) VALUES (N'성기사뿌뿌뿡    ', N'코만도스      ', 250245, 1000050, 1000000, 1000024, CAST(0x9C410188 AS SmallDateTime))
INSERT [dbo].[CHARACTER_BASE] ([characterName], [id], [exper], [gameMoney], [starMoney], [risingStar], [birthday]) VALUES (N'수령님       ', N'qqq       ', 123456, 1000000, 1000000, 1000000, CAST(0x9C3F030A AS SmallDateTime))
INSERT [dbo].[CHARACTER_BASE] ([characterName], [id], [exper], [gameMoney], [starMoney], [risingStar], [birthday]) VALUES (N'시발        ', N'asdasd    ', 1610, 1001050, 1000000, 1000061, CAST(0x9C3C034F AS SmallDateTime))
INSERT [dbo].[CHARACTER_BASE] ([characterName], [id], [exper], [gameMoney], [starMoney], [risingStar], [birthday]) VALUES (N'신성일       ', N'dfg       ', 27396, 1002400, 1004957, 992194, CAST(0x9C4002CB AS SmallDateTime))
INSERT [dbo].[CHARACTER_BASE] ([characterName], [id], [exper], [gameMoney], [starMoney], [risingStar], [birthday]) VALUES (N'신성일투      ', N'saqwe     ', 26827, 955050, 1010093, 983705, CAST(0x9C400402 AS SmallDateTime))
INSERT [dbo].[CHARACTER_BASE] ([characterName], [id], [exper], [gameMoney], [starMoney], [risingStar], [birthday]) VALUES (N'아쭈구리      ', N'abcdef    ', 0, 0, 0, 0, CAST(0x9C450364 AS SmallDateTime))
INSERT [dbo].[CHARACTER_BASE] ([characterName], [id], [exper], [gameMoney], [starMoney], [risingStar], [birthday]) VALUES (N'야메        ', N'kokoro    ', 1060, 600, 0, 46, CAST(0x9C50031A AS SmallDateTime))
INSERT [dbo].[CHARACTER_BASE] ([characterName], [id], [exper], [gameMoney], [starMoney], [risingStar], [birthday]) VALUES (N'얄리몬       ', N'lancekun  ', 0, 10000, 100, 100, CAST(0x9C610320 AS SmallDateTime))
INSERT [dbo].[CHARACTER_BASE] ([characterName], [id], [exper], [gameMoney], [starMoney], [risingStar], [birthday]) VALUES (N'어익쿠       ', N'77777     ', 1290, 8500, 100, 179, CAST(0x9C500275 AS SmallDateTime))
INSERT [dbo].[CHARACTER_BASE] ([characterName], [id], [exper], [gameMoney], [starMoney], [risingStar], [birthday]) VALUES (N'엄앵란       ', N'gugu      ', 577970, 1027350, 1009667, 986780, CAST(0x9C3C0532 AS SmallDateTime))
INSERT [dbo].[CHARACTER_BASE] ([characterName], [id], [exper], [gameMoney], [starMoney], [risingStar], [birthday]) VALUES (N'엔진        ', N'엔ㅋ진ㅋ      ', 13360, 96000, 100345, 100035, CAST(0x9C410195 AS SmallDateTime))
INSERT [dbo].[CHARACTER_BASE] ([characterName], [id], [exper], [gameMoney], [starMoney], [risingStar], [birthday]) VALUES (N'오쿠샤       ', N'a1234     ', 0, 10000, 100, 100, CAST(0x9C5002F3 AS SmallDateTime))
INSERT [dbo].[CHARACTER_BASE] ([characterName], [id], [exper], [gameMoney], [starMoney], [risingStar], [birthday]) VALUES (N'와일드플래닛    ', N'qwerasdf  ', 7870, 13600, 168, 197, CAST(0x9C55026D AS SmallDateTime))
INSERT [dbo].[CHARACTER_BASE] ([characterName], [id], [exper], [gameMoney], [starMoney], [risingStar], [birthday]) VALUES (N'위대한 수령님   ', N'xcv       ', 50000, 1000000, 1000000, 1000000, CAST(0x9C4002D2 AS SmallDateTime))
INSERT [dbo].[CHARACTER_BASE] ([characterName], [id], [exper], [gameMoney], [starMoney], [risingStar], [birthday]) VALUES (N'유희열       ', N'wer       ', 72067, 1019600, 1005531, 995550, CAST(0x9C4002C7 AS SmallDateTime))
INSERT [dbo].[CHARACTER_BASE] ([characterName], [id], [exper], [gameMoney], [starMoney], [risingStar], [birthday]) VALUES (N'장난감       ', N'가나다       ', 0, 10000, 100, 100, CAST(0x9C500287 AS SmallDateTime))
INSERT [dbo].[CHARACTER_BASE] ([characterName], [id], [exper], [gameMoney], [starMoney], [risingStar], [birthday]) VALUES (N'제라드       ', N'제라드       ', 880, 150, 0, 88, CAST(0x9C4302E7 AS SmallDateTime))
INSERT [dbo].[CHARACTER_BASE] ([characterName], [id], [exper], [gameMoney], [starMoney], [risingStar], [birthday]) VALUES (N'젠장        ', N'rkskekfk  ', 0, 0, 0, 0, CAST(0x9C440402 AS SmallDateTime))
INSERT [dbo].[CHARACTER_BASE] ([characterName], [id], [exper], [gameMoney], [starMoney], [risingStar], [birthday]) VALUES (N'째뮌        ', N'viceboss  ', 1190, 10100, 100, 219, CAST(0x9C50033C AS SmallDateTime))
INSERT [dbo].[CHARACTER_BASE] ([characterName], [id], [exper], [gameMoney], [starMoney], [risingStar], [birthday]) VALUES (N'클스        ', N'ktandya   ', 0, 10000, 100, 100, CAST(0x9C7C042C AS SmallDateTime))
INSERT [dbo].[CHARACTER_BASE] ([characterName], [id], [exper], [gameMoney], [starMoney], [risingStar], [birthday]) VALUES (N'타우렌함유     ', N'wow       ', 2560, 1150, 0, 156, CAST(0x9C46038C AS SmallDateTime))
INSERT [dbo].[CHARACTER_BASE] ([characterName], [id], [exper], [gameMoney], [starMoney], [risingStar], [birthday]) VALUES (N'터프가이      ', N'kkh       ', 73316, 966950, 2118630, 253949, CAST(0x9C41018B AS SmallDateTime))
INSERT [dbo].[CHARACTER_BASE] ([characterName], [id], [exper], [gameMoney], [starMoney], [risingStar], [birthday]) VALUES (N'테스트용      ', N'66667     ', 0, 10000, 100, 100, CAST(0x9C5502FB AS SmallDateTime))
INSERT [dbo].[CHARACTER_BASE] ([characterName], [id], [exper], [gameMoney], [starMoney], [risingStar], [birthday]) VALUES (N'판타지 스타    ', N'2462      ', 0, 0, 0, 0, CAST(0x9C440347 AS SmallDateTime))
INSERT [dbo].[CHARACTER_BASE] ([characterName], [id], [exper], [gameMoney], [starMoney], [risingStar], [birthday]) VALUES (N'팡케루       ', N'lightdark ', 530, 100, 0, 53, CAST(0x9C50045D AS SmallDateTime))
INSERT [dbo].[CHARACTER_BASE] ([characterName], [id], [exper], [gameMoney], [starMoney], [risingStar], [birthday]) VALUES (N'푸르푸르      ', N'chaen     ', 0, 10000, 100, 100, CAST(0x9C5004AA AS SmallDateTime))
INSERT [dbo].[CHARACTER_BASE] ([characterName], [id], [exper], [gameMoney], [starMoney], [risingStar], [birthday]) VALUES (N'한승연       ', N'안아줘승연아    ', 370, 3050, 106, 37, CAST(0x9C6102B3 AS SmallDateTime))
INSERT [dbo].[CHARACTER_BASE] ([characterName], [id], [exper], [gameMoney], [starMoney], [risingStar], [birthday]) VALUES (N'후훗        ', N'101010    ', 2220, 2500, 80, 0, CAST(0x9C50035F AS SmallDateTime))
INSERT [dbo].[CHARACTER_BASE] ([characterName], [id], [exper], [gameMoney], [starMoney], [risingStar], [birthday]) VALUES (N'휘플휘플      ', N'휘플휘플      ', 1170, 3150, 74, 7, CAST(0x9C50045A AS SmallDateTime))
INSERT [dbo].[CHARACTER_BASE] ([characterName], [id], [exper], [gameMoney], [starMoney], [risingStar], [birthday]) VALUES (N'aaa       ', N'aa        ', 0, 10000, 100, 100, CAST(0x9C50034C AS SmallDateTime))
INSERT [dbo].[CHARACTER_BASE] ([characterName], [id], [exper], [gameMoney], [starMoney], [risingStar], [birthday]) VALUES (N'aaaaaf    ', N'aaad      ', 0, 10000, 100, 100, CAST(0x9C50043E AS SmallDateTime))
INSERT [dbo].[CHARACTER_BASE] ([characterName], [id], [exper], [gameMoney], [starMoney], [risingStar], [birthday]) VALUES (N'aka       ', N'6666      ', 1070, 550, 0, 57, CAST(0x9C4E005C AS SmallDateTime))
INSERT [dbo].[CHARACTER_BASE] ([characterName], [id], [exper], [gameMoney], [starMoney], [risingStar], [birthday]) VALUES (N'asd       ', N'000000    ', 740, 50, 0, 74, CAST(0x9C550381 AS SmallDateTime))
INSERT [dbo].[CHARACTER_BASE] ([characterName], [id], [exper], [gameMoney], [starMoney], [risingStar], [birthday]) VALUES (N'asdd      ', N'1233      ', 0, 10000, 100, 100, CAST(0x9CA202DD AS SmallDateTime))
INSERT [dbo].[CHARACTER_BASE] ([characterName], [id], [exper], [gameMoney], [starMoney], [risingStar], [birthday]) VALUES (N'asdf      ', N'flybird   ', 0, 10000, 100, 100, CAST(0x9C5003CD AS SmallDateTime))
INSERT [dbo].[CHARACTER_BASE] ([characterName], [id], [exper], [gameMoney], [starMoney], [risingStar], [birthday]) VALUES (N'blackhole ', N'AB123     ', 0, 10000, 100, 100, CAST(0x9C500325 AS SmallDateTime))
INSERT [dbo].[CHARACTER_BASE] ([characterName], [id], [exper], [gameMoney], [starMoney], [risingStar], [birthday]) VALUES (N'dddd      ', N'aaaa      ', 0, 10000, 100, 100, CAST(0x9C5002D6 AS SmallDateTime))
INSERT [dbo].[CHARACTER_BASE] ([characterName], [id], [exper], [gameMoney], [starMoney], [risingStar], [birthday]) VALUES (N'ddwee     ', N'asdd      ', 0, 10000, 100, 100, CAST(0x9CA202E1 AS SmallDateTime))
INSERT [dbo].[CHARACTER_BASE] ([characterName], [id], [exper], [gameMoney], [starMoney], [risingStar], [birthday]) VALUES (N'dma..     ', N'aaaaa     ', 520, 1400, 72, 12, CAST(0x9C51054F AS SmallDateTime))
INSERT [dbo].[CHARACTER_BASE] ([characterName], [id], [exper], [gameMoney], [starMoney], [risingStar], [birthday]) VALUES (N'DREAMEXE  ', N'GGGG      ', 0, 10000, 100, 100, CAST(0x9C50030C AS SmallDateTime))
INSERT [dbo].[CHARACTER_BASE] ([characterName], [id], [exper], [gameMoney], [starMoney], [risingStar], [birthday]) VALUES (N'ds        ', N'xwvvwx    ', 0, 3000, 70, 10, CAST(0x9C520329 AS SmallDateTime))
INSERT [dbo].[CHARACTER_BASE] ([characterName], [id], [exper], [gameMoney], [starMoney], [risingStar], [birthday]) VALUES (N'dsscsd    ', N'besoul    ', 0, 10000, 100, 100, CAST(0x9C500415 AS SmallDateTime))
INSERT [dbo].[CHARACTER_BASE] ([characterName], [id], [exper], [gameMoney], [starMoney], [risingStar], [birthday]) VALUES (N'exxa      ', N'exxa      ', 102187, 1020850, 1231440, 573232, CAST(0x9C3C0505 AS SmallDateTime))
INSERT [dbo].[CHARACTER_BASE] ([characterName], [id], [exper], [gameMoney], [starMoney], [risingStar], [birthday]) VALUES (N'fdsfdsf   ', N'abcdsp    ', 0, 10000, 100, 100, CAST(0x9C5003CD AS SmallDateTime))
INSERT [dbo].[CHARACTER_BASE] ([characterName], [id], [exper], [gameMoney], [starMoney], [risingStar], [birthday]) VALUES (N'ff        ', N'eedd      ', 1420, 1050, 0, 42, CAST(0x9C5003B9 AS SmallDateTime))
INSERT [dbo].[CHARACTER_BASE] ([characterName], [id], [exper], [gameMoney], [starMoney], [risingStar], [birthday]) VALUES (N'KGDA      ', N'kgda      ', 0, 5000, 92, 0, CAST(0x9C73023F AS SmallDateTime))
INSERT [dbo].[CHARACTER_BASE] ([characterName], [id], [exper], [gameMoney], [starMoney], [risingStar], [birthday]) VALUES (N'Luna      ', N'wp        ', 2395818, 77250, 177545, 48397, CAST(0x9C410197 AS SmallDateTime))
INSERT [dbo].[CHARACTER_BASE] ([characterName], [id], [exper], [gameMoney], [starMoney], [risingStar], [birthday]) VALUES (N'mOok      ', N'mook      ', 700, 2500, 100, 120, CAST(0x9C5002E4 AS SmallDateTime))
INSERT [dbo].[CHARACTER_BASE] ([characterName], [id], [exper], [gameMoney], [starMoney], [risingStar], [birthday]) VALUES (N'ppp       ', N'ppp       ', 0, 0, 10, 100, CAST(0x9C6B02F2 AS SmallDateTime))
INSERT [dbo].[CHARACTER_BASE] ([characterName], [id], [exper], [gameMoney], [starMoney], [risingStar], [birthday]) VALUES (N'pppp      ', N'pppp      ', 0, 10000, 100, 100, CAST(0x9C6C0245 AS SmallDateTime))
INSERT [dbo].[CHARACTER_BASE] ([characterName], [id], [exper], [gameMoney], [starMoney], [risingStar], [birthday]) VALUES (N'ppppp     ', N'ppppp     ', 0, 10000, 100, 100, CAST(0x9C6D03C9 AS SmallDateTime))
INSERT [dbo].[CHARACTER_BASE] ([characterName], [id], [exper], [gameMoney], [starMoney], [risingStar], [birthday]) VALUES (N'qwer      ', N'qwer      ', 1500, 600, 0, 100, CAST(0x9C410323 AS SmallDateTime))
INSERT [dbo].[CHARACTER_BASE] ([characterName], [id], [exper], [gameMoney], [starMoney], [risingStar], [birthday]) VALUES (N'sam       ', N'carobe    ', 0, 10000, 100, 100, CAST(0x9C5504DD AS SmallDateTime))
INSERT [dbo].[CHARACTER_BASE] ([characterName], [id], [exper], [gameMoney], [starMoney], [risingStar], [birthday]) VALUES (N'select    ', N'sp        ', 14567, 1000000, 1000000, 1000000, CAST(0x9C3F02EC AS SmallDateTime))
INSERT [dbo].[CHARACTER_BASE] ([characterName], [id], [exper], [gameMoney], [starMoney], [risingStar], [birthday]) VALUES (N'ss        ', N'as        ', 0, 10000, 100, 100, CAST(0x9C5604A2 AS SmallDateTime))
INSERT [dbo].[CHARACTER_BASE] ([characterName], [id], [exper], [gameMoney], [starMoney], [risingStar], [birthday]) VALUES (N'test      ', N'111       ', 1640, 900, 40, 74, CAST(0x9C4E03D2 AS SmallDateTime))
INSERT [dbo].[CHARACTER_BASE] ([characterName], [id], [exper], [gameMoney], [starMoney], [risingStar], [birthday]) VALUES (N'test1     ', N'test1     ', 28747, 996000, 1026671, 965024, CAST(0x9C3D0345 AS SmallDateTime))
INSERT [dbo].[CHARACTER_BASE] ([characterName], [id], [exper], [gameMoney], [starMoney], [risingStar], [birthday]) VALUES (N'test2     ', N'test2     ', 23347, 990300, 1955753, 318955, CAST(0x9C3D0346 AS SmallDateTime))
INSERT [dbo].[CHARACTER_BASE] ([characterName], [id], [exper], [gameMoney], [starMoney], [risingStar], [birthday]) VALUES (N'test3     ', N'test3     ', 0, 10000, 100, 100, CAST(0x9C4E03AA AS SmallDateTime))
INSERT [dbo].[CHARACTER_BASE] ([characterName], [id], [exper], [gameMoney], [starMoney], [risingStar], [birthday]) VALUES (N'xkall     ', N'kallru    ', 0, 10000, 100, 100, CAST(0x9C50049C AS SmallDateTime))
INSERT [dbo].[CHARACTER_BASE] ([characterName], [id], [exper], [gameMoney], [starMoney], [risingStar], [birthday]) VALUES (N'zzz       ', N'zzz       ', 14567, 1000000, 1000000, 1000000, CAST(0x9C3F02CF AS SmallDateTime))
/****** Object:  Table [dbo].[ITEM_AVATAR]    Script Date: 10/29/2018 19:50:20 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[ITEM_AVATAR](
	[itemCode] [int] NOT NULL,
	[itemName] [nchar](20) NOT NULL,
	[avatarCategory] [int] NOT NULL,
	[avatarPrice] [int] NOT NULL,
 CONSTRAINT [PK__ITEM_AVATAR] PRIMARY KEY CLUSTERED 
(
	[itemCode] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
INSERT [dbo].[ITEM_AVATAR] ([itemCode], [itemName], [avatarCategory], [avatarPrice]) VALUES (40001, N'밀짚 모자               ', 40000, 5000)
INSERT [dbo].[ITEM_AVATAR] ([itemCode], [itemName], [avatarCategory], [avatarPrice]) VALUES (40002, N'머리 핀                ', 40000, 5000)
INSERT [dbo].[ITEM_AVATAR] ([itemCode], [itemName], [avatarCategory], [avatarPrice]) VALUES (50001, N'초록색                 ', 50000, 1000)
INSERT [dbo].[ITEM_AVATAR] ([itemCode], [itemName], [avatarCategory], [avatarPrice]) VALUES (50002, N'코코아색                ', 50000, 1000)
INSERT [dbo].[ITEM_AVATAR] ([itemCode], [itemName], [avatarCategory], [avatarPrice]) VALUES (50003, N'오렌지색                ', 50000, 1000)
INSERT [dbo].[ITEM_AVATAR] ([itemCode], [itemName], [avatarCategory], [avatarPrice]) VALUES (50004, N'노란색                 ', 50000, 1000)
INSERT [dbo].[ITEM_AVATAR] ([itemCode], [itemName], [avatarCategory], [avatarPrice]) VALUES (50011, N'빨강색                 ', 50000, 1000)
INSERT [dbo].[ITEM_AVATAR] ([itemCode], [itemName], [avatarCategory], [avatarPrice]) VALUES (50012, N'파란색                 ', 50000, 1000)
INSERT [dbo].[ITEM_AVATAR] ([itemCode], [itemName], [avatarCategory], [avatarPrice]) VALUES (60001, N'별                   ', 60000, 2000)
INSERT [dbo].[ITEM_AVATAR] ([itemCode], [itemName], [avatarCategory], [avatarPrice]) VALUES (60002, N'달                   ', 60000, 2000)
INSERT [dbo].[ITEM_AVATAR] ([itemCode], [itemName], [avatarCategory], [avatarPrice]) VALUES (60003, N'성게                  ', 60000, 2000)
INSERT [dbo].[ITEM_AVATAR] ([itemCode], [itemName], [avatarCategory], [avatarPrice]) VALUES (60004, N'더스트                 ', 60000, 2000)
INSERT [dbo].[ITEM_AVATAR] ([itemCode], [itemName], [avatarCategory], [avatarPrice]) VALUES (60005, N'루아비통(명품)            ', 60000, 3000)
INSERT [dbo].[ITEM_AVATAR] ([itemCode], [itemName], [avatarCategory], [avatarPrice]) VALUES (60006, N'나이키                 ', 60000, 3000)
INSERT [dbo].[ITEM_AVATAR] ([itemCode], [itemName], [avatarCategory], [avatarPrice]) VALUES (60007, N'KGCA                ', 60000, 3000)
INSERT [dbo].[ITEM_AVATAR] ([itemCode], [itemName], [avatarCategory], [avatarPrice]) VALUES (60008, N'화관                  ', 60000, 5000)
INSERT [dbo].[ITEM_AVATAR] ([itemCode], [itemName], [avatarCategory], [avatarPrice]) VALUES (70001, N'루나                  ', 70000, 10000)
INSERT [dbo].[ITEM_AVATAR] ([itemCode], [itemName], [avatarCategory], [avatarPrice]) VALUES (70002, N'루아                  ', 70000, 10000)
/****** Object:  Table [dbo].[ITEM_OBJECT]    Script Date: 10/29/2018 19:50:20 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[ITEM_OBJECT](
	[itemCode] [int] NOT NULL,
	[itemName] [nchar](20) NOT NULL,
	[objectCategory] [int] NOT NULL,
	[objectSize] [tinyint] NOT NULL,
	[objectPrice] [int] NOT NULL,
 CONSTRAINT [PK__ITEM_OBJECT] PRIMARY KEY CLUSTERED 
(
	[itemCode] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
INSERT [dbo].[ITEM_OBJECT] ([itemCode], [itemName], [objectCategory], [objectSize], [objectPrice]) VALUES (11011, N'미치광이 광대 버섯(대)       ', 10000, 1, 50)
INSERT [dbo].[ITEM_OBJECT] ([itemCode], [itemName], [objectCategory], [objectSize], [objectPrice]) VALUES (11021, N'독 포자 버섯(녹색)         ', 10000, 1, 60)
INSERT [dbo].[ITEM_OBJECT] ([itemCode], [itemName], [objectCategory], [objectSize], [objectPrice]) VALUES (11022, N'독 포자 버섯(보라색)        ', 10000, 1, 60)
INSERT [dbo].[ITEM_OBJECT] ([itemCode], [itemName], [objectCategory], [objectSize], [objectPrice]) VALUES (11031, N'독 가시 버섯             ', 10000, 1, 70)
INSERT [dbo].[ITEM_OBJECT] ([itemCode], [itemName], [objectCategory], [objectSize], [objectPrice]) VALUES (11041, N'꼬꼬마 버섯(흰색)          ', 10000, 1, 50)
INSERT [dbo].[ITEM_OBJECT] ([itemCode], [itemName], [objectCategory], [objectSize], [objectPrice]) VALUES (11042, N'꼬꼬마 버섯(핑크색)         ', 10000, 1, 50)
INSERT [dbo].[ITEM_OBJECT] ([itemCode], [itemName], [objectCategory], [objectSize], [objectPrice]) VALUES (12011, N'금이간 전구(흰색)          ', 10000, 3, 100)
INSERT [dbo].[ITEM_OBJECT] ([itemCode], [itemName], [objectCategory], [objectSize], [objectPrice]) VALUES (12012, N'금이간 전구(빨강)          ', 10000, 3, 100)
INSERT [dbo].[ITEM_OBJECT] ([itemCode], [itemName], [objectCategory], [objectSize], [objectPrice]) VALUES (12013, N'금이간 전구(녹색)          ', 10000, 3, 100)
INSERT [dbo].[ITEM_OBJECT] ([itemCode], [itemName], [objectCategory], [objectSize], [objectPrice]) VALUES (12021, N'오래된 가로등(흰색)         ', 10000, 1, 70)
INSERT [dbo].[ITEM_OBJECT] ([itemCode], [itemName], [objectCategory], [objectSize], [objectPrice]) VALUES (12022, N'오래된 가로등(빨강)         ', 10000, 1, 70)
INSERT [dbo].[ITEM_OBJECT] ([itemCode], [itemName], [objectCategory], [objectSize], [objectPrice]) VALUES (12023, N'오래된 가로등(녹색)         ', 10000, 1, 70)
INSERT [dbo].[ITEM_OBJECT] ([itemCode], [itemName], [objectCategory], [objectSize], [objectPrice]) VALUES (12031, N'초롱꽃(녹색)             ', 10000, 1, 90)
INSERT [dbo].[ITEM_OBJECT] ([itemCode], [itemName], [objectCategory], [objectSize], [objectPrice]) VALUES (12032, N'초롱꽃(얼음)             ', 10000, 1, 90)
INSERT [dbo].[ITEM_OBJECT] ([itemCode], [itemName], [objectCategory], [objectSize], [objectPrice]) VALUES (12033, N'초롱꽃(녹슨은색)           ', 10000, 1, 90)
INSERT [dbo].[ITEM_OBJECT] ([itemCode], [itemName], [objectCategory], [objectSize], [objectPrice]) VALUES (13011, N'화산(진갈색)             ', 10000, 6, 200)
INSERT [dbo].[ITEM_OBJECT] ([itemCode], [itemName], [objectCategory], [objectSize], [objectPrice]) VALUES (13021, N'탄나무(검은색)            ', 10000, 1, 70)
INSERT [dbo].[ITEM_OBJECT] ([itemCode], [itemName], [objectCategory], [objectSize], [objectPrice]) VALUES (13031, N'돌맹이(검은색)            ', 10000, 1, 50)
INSERT [dbo].[ITEM_OBJECT] ([itemCode], [itemName], [objectCategory], [objectSize], [objectPrice]) VALUES (14041, N'죽은나무 그루터기(검은색)      ', 10000, 3, 100)
INSERT [dbo].[ITEM_OBJECT] ([itemCode], [itemName], [objectCategory], [objectSize], [objectPrice]) VALUES (14051, N'짐승의 머리 뼈(검은색)       ', 10000, 2, 70)
INSERT [dbo].[ITEM_OBJECT] ([itemCode], [itemName], [objectCategory], [objectSize], [objectPrice]) VALUES (14071, N'갈비 뼈(검은색)           ', 10000, 2, 90)
INSERT [dbo].[ITEM_OBJECT] ([itemCode], [itemName], [objectCategory], [objectSize], [objectPrice]) VALUES (16011, N'야자수(녹색)             ', 10000, 1, 100)
INSERT [dbo].[ITEM_OBJECT] ([itemCode], [itemName], [objectCategory], [objectSize], [objectPrice]) VALUES (16012, N'야자수(얼음색)            ', 10000, 1, 100)
INSERT [dbo].[ITEM_OBJECT] ([itemCode], [itemName], [objectCategory], [objectSize], [objectPrice]) VALUES (16022, N'이글루(분홍색)            ', 10000, 3, 150)
INSERT [dbo].[ITEM_OBJECT] ([itemCode], [itemName], [objectCategory], [objectSize], [objectPrice]) VALUES (16023, N'이글루(하늘색)            ', 10000, 3, 150)
INSERT [dbo].[ITEM_OBJECT] ([itemCode], [itemName], [objectCategory], [objectSize], [objectPrice]) VALUES (17011, N'작은집                 ', 10000, 6, 0)
INSERT [dbo].[ITEM_OBJECT] ([itemCode], [itemName], [objectCategory], [objectSize], [objectPrice]) VALUES (31001, N'보라 독 지대             ', 30000, 0, 20)
INSERT [dbo].[ITEM_OBJECT] ([itemCode], [itemName], [objectCategory], [objectSize], [objectPrice]) VALUES (31002, N'녹색 독 지대             ', 30000, 0, 20)
INSERT [dbo].[ITEM_OBJECT] ([itemCode], [itemName], [objectCategory], [objectSize], [objectPrice]) VALUES (32001, N'풀밭01                ', 30000, 0, 20)
INSERT [dbo].[ITEM_OBJECT] ([itemCode], [itemName], [objectCategory], [objectSize], [objectPrice]) VALUES (32002, N'풀밭02                ', 30000, 0, 20)
INSERT [dbo].[ITEM_OBJECT] ([itemCode], [itemName], [objectCategory], [objectSize], [objectPrice]) VALUES (32003, N'풀밭03                ', 30000, 0, 20)
INSERT [dbo].[ITEM_OBJECT] ([itemCode], [itemName], [objectCategory], [objectSize], [objectPrice]) VALUES (33001, N'황무지                 ', 30000, 0, 20)
INSERT [dbo].[ITEM_OBJECT] ([itemCode], [itemName], [objectCategory], [objectSize], [objectPrice]) VALUES (33002, N'모래                  ', 30000, 0, 20)
INSERT [dbo].[ITEM_OBJECT] ([itemCode], [itemName], [objectCategory], [objectSize], [objectPrice]) VALUES (33003, N'갈색 땅                ', 30000, 0, 20)
INSERT [dbo].[ITEM_OBJECT] ([itemCode], [itemName], [objectCategory], [objectSize], [objectPrice]) VALUES (34001, N'검은 흙땅               ', 30000, 0, 20)
INSERT [dbo].[ITEM_OBJECT] ([itemCode], [itemName], [objectCategory], [objectSize], [objectPrice]) VALUES (35001, N'용암                  ', 30000, 0, 20)
INSERT [dbo].[ITEM_OBJECT] ([itemCode], [itemName], [objectCategory], [objectSize], [objectPrice]) VALUES (35002, N'화산길                 ', 30000, 0, 20)
INSERT [dbo].[ITEM_OBJECT] ([itemCode], [itemName], [objectCategory], [objectSize], [objectPrice]) VALUES (36001, N'유황                  ', 30000, 0, 20)
INSERT [dbo].[ITEM_OBJECT] ([itemCode], [itemName], [objectCategory], [objectSize], [objectPrice]) VALUES (37001, N'눈                   ', 30000, 0, 20)
INSERT [dbo].[ITEM_OBJECT] ([itemCode], [itemName], [objectCategory], [objectSize], [objectPrice]) VALUES (37002, N'얼음                  ', 30000, 0, 20)
INSERT [dbo].[ITEM_OBJECT] ([itemCode], [itemName], [objectCategory], [objectSize], [objectPrice]) VALUES (38001, N'철판(검정)              ', 30000, 0, 20)
INSERT [dbo].[ITEM_OBJECT] ([itemCode], [itemName], [objectCategory], [objectSize], [objectPrice]) VALUES (38002, N'철판(회색)              ', 30000, 0, 20)
INSERT [dbo].[ITEM_OBJECT] ([itemCode], [itemName], [objectCategory], [objectSize], [objectPrice]) VALUES (80001, N'Aquarius            ', 80000, 0, 0)
INSERT [dbo].[ITEM_OBJECT] ([itemCode], [itemName], [objectCategory], [objectSize], [objectPrice]) VALUES (80002, N'Pisces              ', 80000, 0, 0)
INSERT [dbo].[ITEM_OBJECT] ([itemCode], [itemName], [objectCategory], [objectSize], [objectPrice]) VALUES (80003, N'Aries               ', 80000, 0, 0)
INSERT [dbo].[ITEM_OBJECT] ([itemCode], [itemName], [objectCategory], [objectSize], [objectPrice]) VALUES (80004, N'Taurus              ', 80000, 0, 0)
INSERT [dbo].[ITEM_OBJECT] ([itemCode], [itemName], [objectCategory], [objectSize], [objectPrice]) VALUES (80005, N'Gemini              ', 80000, 0, 0)
INSERT [dbo].[ITEM_OBJECT] ([itemCode], [itemName], [objectCategory], [objectSize], [objectPrice]) VALUES (80006, N'Cancer              ', 80000, 0, 0)
INSERT [dbo].[ITEM_OBJECT] ([itemCode], [itemName], [objectCategory], [objectSize], [objectPrice]) VALUES (80007, N'Leo                 ', 80000, 0, 0)
INSERT [dbo].[ITEM_OBJECT] ([itemCode], [itemName], [objectCategory], [objectSize], [objectPrice]) VALUES (80008, N'Virgo               ', 80000, 0, 0)
INSERT [dbo].[ITEM_OBJECT] ([itemCode], [itemName], [objectCategory], [objectSize], [objectPrice]) VALUES (80009, N'Libra               ', 80000, 0, 0)
INSERT [dbo].[ITEM_OBJECT] ([itemCode], [itemName], [objectCategory], [objectSize], [objectPrice]) VALUES (80010, N'Scorpius            ', 80000, 0, 0)
INSERT [dbo].[ITEM_OBJECT] ([itemCode], [itemName], [objectCategory], [objectSize], [objectPrice]) VALUES (80011, N'Sagittarius         ', 80000, 0, 0)
INSERT [dbo].[ITEM_OBJECT] ([itemCode], [itemName], [objectCategory], [objectSize], [objectPrice]) VALUES (80012, N'Capricornus         ', 80000, 0, 0)
/****** Object:  StoredProcedure [dbo].[usp_ChangePWAccount]    Script Date: 10/29/2018 19:50:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
---------------------------
-- 객체이름 : dbo.usp_ChangePWAccount
-- 파라미터 : @pmId	NCHAR(10),	@pmPw	NCHAR(10),	@pmNPw	NCHAR(10)
-- 제작자 : baboruri
-- 제작일 : 09-05-30
-- 변경일 : 
-- 내용 : 계정 비번 변경.
-- 결과
-- 비번 변경 성공 : 0
-- 비번이 틀리면 : 1
---------------------------
CREATE PROCEDURE [dbo].[usp_ChangePWAccount]
	@pmId	NCHAR(10),
	@pmPw	NCHAR(10),
	@pmNPw NCHAR(10)
AS
	SET NOCOUNT ON
	
	DECLARE @tmpPw NCHAR(10) = N''
	
	SELECT @tmpPw = pw
	FROM ACCOUNT
	WHERE id = @pmId
	
	-- 비번이 틀리면.
	IF( @pmPw <> @tmpPw )
		BEGIN
			RETURN 1;
		END
		
	UPDATE ACCOUNT
	SET pw = @pmNPW
	WHERE id = @pmId
		
	RETURN 0;
GO
/****** Object:  StoredProcedure [dbo].[usp_CreateAccount]    Script Date: 10/29/2018 19:50:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
---------------------------
-- 객체이름 : dbo.usp_CreateAccount
-- 파라미터 : @pmId	NCHAR(10),	@pmPw	NCHAR(10),	@pmPName	NCHAR(10),	@pmPId	NCHAR(13),	@pmEm NCHAR(30)
-- 제작자 : baboruri
-- 제작일 : 09-05-30
-- 변경일 : 
-- 내용 : 계정 생성.
-- 결과
-- 계정 생생에 성공 Return : 0;
-- PrimaryKey 중복일 때 Return : 1
-- Unique 중복일 때 Return : 2
---------------------------
CREATE PROCEDURE [dbo].[usp_CreateAccount]
	@pmId	NCHAR(10),
	@pmPw	NCHAR(10),
	@pmPName	NCHAR(10),
	@pmPId	NCHAR(13),
	@pmEm NCHAR(30)
AS
	SET NOCOUNT ON
	
	BEGIN TRY
		INSERT INTO ACCOUNT( id, pw, personName, personId, eMail, accountCreate )
		VALUES( LOWER(@pmId), @pmPw, @pmPName, @pmPId, @pmEm, default );
			
		RETURN 0;
	END TRY
		
	BEGIN CATCH
		DECLARE @ret NCHAR(10)
		
		SELECT @ret = id
		FROM ACCOUNT
		WHERE id = @pmId

		-- 이미 존재하는 ID라면 1.
		IF( @ret <> N'' )
			BEGIN
				RETURN 1;
			END
			
		-- 이미 존재하는 personId라면 2.
		RETURN 2;		
	END CATCH
GO
/****** Object:  StoredProcedure [dbo].[usp_InsertDeal]    Script Date: 10/29/2018 19:50:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
---------------------------
-- 객체이름 : dbo.usp_InsertDeal
-- 파라미터 : @pmMode	TINYINT,	@pmStr NCHAR(10)
-- 제작자 : baboruri
-- 제작일 : 09-06-02
-- 변경일 : 
-- 내용 : 거래 모드 추가.
-- 결과
-- 생생에 성공 Return : 0;
-- PrimaryKey 중복일 때 Return : 1
---------------------------
CREATE PROCEDURE [dbo].[usp_InsertDeal]
	@pmMode	TINYINT,
	@pmStr		NCHAR(10)
AS
	SET NOCOUNT ON
	
	BEGIN TRY
		INSERT INTO DEAL_MODE( dealMode, dealStr )
		VALUES( @pmMode, @pmStr )
		
		RETURN 0;
	END TRY
	
	BEGIN CATCH
		RETURN 1;
	END CATCH
GO
/****** Object:  StoredProcedure [dbo].[usp_LogoutAccount]    Script Date: 10/29/2018 19:50:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
---------------------------
-- 객체이름 : dbo.usp_LogoutAccount
-- 파라미터 : @pmId	NCHAR(10)
-- 제작자 : baboruri
-- 제작일 : 09-05-30
-- 변경일 : 
-- 내용 : 계정 로그아웃.
-- 결과
-- 성공 : 0
---------------------------
CREATE PROCEDURE [dbo].[usp_LogoutAccount]
	@pmId	NCHAR(10)
AS
	SET NOCOUNT ON	
	
	UPDATE ACCOUNT
	SET logoutTime = GETDATE()
	WHERE id = @pmId
	
	RETURN 0;
GO
/****** Object:  StoredProcedure [dbo].[usp_LoginAccount]    Script Date: 10/29/2018 19:50:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
---------------------------
-- 객체이름 : dbo.usp_LoginAccount
-- 파라미터 : @pmId	NCHAR(10),	@pmPw	NCHAR(10)
-- 제작자 : baboruri
-- 제작일 : 09-05-30
-- 변경일 : 
-- 내용 : 계정 로그인.
-- 결과
-- 로그인 성공 : 0
-- 아이디 없음 : 1
-- 비번이 틀림 : 2
---------------------------
CREATE PROCEDURE [dbo].[usp_LoginAccount]
	@pmId	NCHAR(10),
	@pmPw	NCHAR(10)
AS
	SET NOCOUNT ON
	
	DECLARE @tmpPw NCHAR(10) = N''
	
	SELECT @tmpPw = pw
	FROM ACCOUNT
	WHERE id = @pmId
	
	-- 아이디가 없으면 1
	IF( N'' = @tmpPw )
		BEGIN
			RETURN 1;
		END
	-- 비번이 틀리면 2.
	IF( @pmPw <> @tmpPw )
		BEGIN
			RETURN 2;
		END
	
	UPDATE ACCOUNT
	SET loginTime = GETDATE()
	WHERE id = @pmId
		
	-- 성공 0.	
	RETURN 0;
GO
/****** Object:  StoredProcedure [dbo].[usp_DeleteAccount]    Script Date: 10/29/2018 19:50:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
---------------------------
-- 객체이름 : dbo.usp_DeleteAccount
-- 파라미터 : @pmId	NCHAR(10),	@pmPw	NCHAR(10),	@pmPId	NCHAR(13)
-- 제작자 : baboruri
-- 제작일 : 09-05-30
-- 변경일 : 
-- 내용 : 계정 삭제.
-- 결과
-- 계정 삭제 성공 : 0
-- 아이디가 없으면 : 1
-- 비번이 틀리면 : 2
-- 민번이 틀리면 : 3
---------------------------
CREATE PROCEDURE [dbo].[usp_DeleteAccount]
	@pmId	NCHAR(10),
	@pmPw	NCHAR(10),
	@pmPId	NCHAR(13)
AS
	SET NOCOUNT ON
	
	DECLARE @tmpPw NCHAR(10) = N''
	DECLARE @tmpPId NCHAR(13) = N''
		
	SELECT @tmpPw = pw, @tmpPId = personId
	FROM ACCOUNT
	WHERE id = @pmId
	
	-- 아이디가 없으면 1.
	IF( N'' = @tmpPw )
		BEGIN
			RETURN 1;
		END
	-- 비번이 틀리면 2.
	IF( @pmPw <> @tmpPw )
		BEGIN
			RETURN 2;
		END
	-- 민번번이 틀리면 3.
	IF( @pmPId <> @tmpPId )
		BEGIN
			RETURN 3;
		END
	
	DELETE ACCOUNT
	WHERE id = @pmId
	
	-- 성공하면 0.
	RETURN 0;
GO
/****** Object:  StoredProcedure [dbo].[usp_FindAccount]    Script Date: 10/29/2018 19:50:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
---------------------------
-- 객체이름 : dbo.usp_FindAccount
-- 파라미터 : @pmPName	NCHAR(10),	@pmPId	NCHAR(13),	@outId	NCHAR(10),	@outPw	NCHAR(10),	
-- 제작자 : baboruri
-- 제작일 : 09-05-30
-- 변경일 : 
-- 내용 : 계정 찾기.
-- 결과
-- 성공 : 0
-- 민번이 없으면 : 1
-- 이름이 안맞으면 : 2
---------------------------
CREATE PROCEDURE [dbo].[usp_FindAccount]
	@pmPName	NCHAR(10),
	@pmPId		NCHAR(13),
	@outId		NVARCHAR(10) OUTPUT,
	@outPw		NVARCHAR(10) OUTPUT
AS
	SET NOCOUNT ON
	
	DECLARE @tmpPName	NCHAR(10) = N''
	DECLARE @tmpPId	NCHAR(13) = N''
	
	SELECT @outId = RTRIM(id), @outPw = RTRIM(pw), @tmpPName = personName, @tmpPId = personId
	FROM ACCOUNT
	WHERE personId = @pmPId
	
	-- 민번이 없으면 1
	IF( N'' = @tmpPId )
		BEGIN
			RETURN 1;
		END
		
	-- 이름이 맞지 않는다. 2
	IF( @pmPName <> @tmpPName )
		BEGIN
			RETURN 2;
		END
		
	-- 성공
	RETURN 0;
GO
/****** Object:  StoredProcedure [dbo].[usp_SetCharacter]    Script Date: 10/29/2018 19:50:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
---------------------------
-- 객체이름 : dbo.usp_SetCharacter
-- 파라미터 :	@pmName NCHAR(10), @pmExp INT, @pmGMoney INT, @pmSMoney INT, @pmRStar INT
-- 제작자 : baboruri
-- 제작일 : 09-06-01
-- 변경일 : 
-- 내용 : 케릭터 정보 얻어오기
-- 결과
-- 성공 Return : 0;
---------------------------
CREATE PROCEDURE [dbo].[usp_SetCharacter]
	@pmName		NCHAR(10),
	@pmExp			INT,
	@pmGMoney	INT,
	@pmSMoney	INT,
	@pmRStar		INT
AS
	SET NOCOUNT ON
	
	-- +=이 아니라 그냥 서버에서 어짜피 계산하니까 그냥 그 값 그대로 추가 하도록 하자.
	UPDATE CHARACTER_BASE
	SET exper = @pmExp, gameMoney = @pmGMoney, starMoney = @pmSMoney, risingStar = @pmRStar
	WHERE characterName = @pmName 
	
	RETURN 0
GO
/****** Object:  StoredProcedure [dbo].[usp_InsertObject]    Script Date: 10/29/2018 19:50:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
---------------------------
-- 객체이름 : dbo.usp_InsertObject
-- 파라미터 : @itemCode INT, @itemName NCHAR(20), @objectCategory INT, @objectsSize TINYINT, @objectPrice INT
-- 제작자 : baboruri
-- 제작일 : 09-06-02
-- 변경일 : 
-- 내용 : 오브젝트 목록 추가.
-- 결과
-- 생생에 성공 Return : 0;
-- PrimaryKey 중복일 때 Return : 1
---------------------------
CREATE PROCEDURE [dbo].[usp_InsertObject]
	@itemCode			INT,
	@itemName			NCHAR(20),
	@objectCategory	INT,
	@objectSize			TINYINT,
	@objectPrice			INT
AS
	SET NOCOUNT ON

	BEGIN TRY
		INSERT INTO ITEM_OBJECT( itemCode, itemName, objectCategory, objectSize, objectPrice )
		VALUES( @itemCode, @itemName, @objectCategory, @objectSize, @objectPrice )
		
		RETURN 0;
	END TRY
	
	BEGIN CATCH
		RETURN 1;
	END CATCH
GO
/****** Object:  StoredProcedure [dbo].[usp_InsertAvatar]    Script Date: 10/29/2018 19:50:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
---------------------------
-- 객체이름 : dbo.usp_InsertAvatar
-- 파라미터 : @itemCode INT, @itemName NCHAR(20), @avatarCategory INT, @avatarPrice INT
-- 제작자 : baboruri
-- 제작일 : 09-06-02
-- 변경일 : 
-- 내용 : 아바타 아이템 목록 추가.
-- 결과
-- 생생에 성공 Return : 0;
-- PrimaryKey 중복일 때 Return : 1
---------------------------
CREATE PROCEDURE [dbo].[usp_InsertAvatar]
	@itemCode			INT,
	@itemName			NCHAR(20),
	@avatarCategory	INT,
	@avatarPrice			INT
AS
	SET NOCOUNT ON
	
	BEGIN TRY
		INSERT INTO ITEM_AVATAR( itemCode, itemName, avatarCategory, avatarPrice )
		VALUES( @itemCode, @itemName, @avatarCategory, @avatarPrice )
		
		RETURN 0;
	END TRY
	
	BEGIN CATCH
		RETURN 1;
	END CATCH
GO
/****** Object:  StoredProcedure [dbo].[usp_GetObjectItem]    Script Date: 10/29/2018 19:50:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
---------------------------
-- 객체이름 : dbo.usp_GetObjectItem
-- 파라미터 :
-- 제작자 : baboruri
-- 제작일 : 09-06-22
-- 변경일 : 
-- 내용 : 상점에서 판매되는 행성관련 목록 얻어오기.
-- 결과
-- 성공 Return : 0;
---------------------------
CREATE PROCEDURE [dbo].[usp_GetObjectItem]
AS
	SET NOCOUNT ON
	
	SELECT itemCode, RTRIM(itemName), objectCategory, objectSize, objectPrice
	FROM ITEM_OBJECT
	
	RETURN 0;
GO
/****** Object:  StoredProcedure [dbo].[usp_GetCharacter]    Script Date: 10/29/2018 19:50:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
---------------------------
-- 객체이름 : dbo.usp_GetCharacter
-- 파라미터 :	@pmName NCHAR(10), @pmExp INT OUTPUT, @pmGMoney INT OUTPUT, @pmSMoney INT OUTPUT, @pmRStar INT OUTPUT
-- 제작자 : baboruri
-- 제작일 : 09-06-01
-- 변경일 : 
-- 내용 : 케릭터 정보 얻어오기
-- 결과
-- 성공 Return : 0;
---------------------------
CREATE PROCEDURE [dbo].[usp_GetCharacter]
	@pmId			NCHAR(10),
	@pmName		NVARCHAR(10) OUTPUT,
	@pmExp			INT OUTPUT,
	@pmGMoney	INT OUTPUT,
	@pmSMoney	INT OUTPUT,
	@pmRStar		INT OUTPUT
AS
	SET NOCOUNT ON
	
	SELECT @pmName = RTRIM(characterName), @pmExp = exper, @pmGMoney = gameMoney, @pmSMoney = starMoney, @pmRStar = risingStar
	FROM CHARACTER_BASE
	WHERE id = @pmId
	
	RETURN 0
GO
/****** Object:  StoredProcedure [dbo].[usp_GetAvatarItem]    Script Date: 10/29/2018 19:50:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
---------------------------
-- 객체이름 : dbo.usp_GetAvatarItem
-- 파라미터 :
-- 제작자 : baboruri
-- 제작일 : 09-06-22
-- 변경일 : 
-- 내용 : 상점에서 판매되는 아바타 목록 얻어오기.
-- 결과
-- 성공 Return : 0;
---------------------------
CREATE PROCEDURE [dbo].[usp_GetAvatarItem]
AS
	SET NOCOUNT ON
	
	SELECT itemCode, RTRIM(itemName), avatarCategory, avatarPrice
	FROM ITEM_AVATAR
	
	RETURN 0;
GO
/****** Object:  StoredProcedure [dbo].[usp_DeleteAvatar]    Script Date: 10/29/2018 19:50:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
---------------------------
-- 객체이름 : dbo.usp_DeleteAvatar
-- 파라미터 : @itemCode INT
-- 제작자 : baboruri
-- 제작일 : 09-06-02
-- 변경일 : 
-- 내용 : 아바타 아이템 목록 삭제.
-- 결과
-- 삭제 성공 Return : 0;
-- 삭제 실패 Return : 1;
---------------------------
CREATE PROCEDURE [dbo].[usp_DeleteAvatar]
	@itemCode			INT
AS
	SET NOCOUNT ON
	
	DELETE ITEM_AVATAR
	WHERE itemCode = @itemCode;
GO
/****** Object:  StoredProcedure [dbo].[usp_DeleteObject]    Script Date: 10/29/2018 19:50:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
---------------------------
-- 객체이름 : dbo.usp_DeleteObject
-- 파라미터 : @itemCode INT
-- 제작자 : baboruri
-- 제작일 : 09-06-02
-- 변경일 : 
-- 내용 : 오브젝트 목록 삭제.
-- 결과
-- 삭제 성공 Return : 0;
-- 삭제 실패 Return : 1;
---------------------------
CREATE PROCEDURE [dbo].[usp_DeleteObject]
	@itemCode			INT
AS
	SET NOCOUNT ON
	
	DELETE ITEM_OBJECT
	WHERE itemCode = @itemCode;
GO
/****** Object:  Table [dbo].[PLANET_BASE]    Script Date: 10/29/2018 19:50:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[PLANET_BASE](
	[planetName] [nchar](10) NOT NULL,
	[characterName] [nchar](10) NOT NULL,
 CONSTRAINT [PK__PLANET_BASE] PRIMARY KEY CLUSTERED 
(
	[planetName] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
INSERT [dbo].[PLANET_BASE] ([planetName], [characterName]) VALUES (N'1         ', N'1         ')
INSERT [dbo].[PLANET_BASE] ([planetName], [characterName]) VALUES (N'123       ', N'dma..     ')
INSERT [dbo].[PLANET_BASE] ([planetName], [characterName]) VALUES (N'444       ', N'666       ')
INSERT [dbo].[PLANET_BASE] ([planetName], [characterName]) VALUES (N'446       ', N'asdf      ')
INSERT [dbo].[PLANET_BASE] ([planetName], [characterName]) VALUES (N'6666      ', N'5555      ')
INSERT [dbo].[PLANET_BASE] ([planetName], [characterName]) VALUES (N'개터프       ', N'터프가이      ')
INSERT [dbo].[PLANET_BASE] ([planetName], [characterName]) VALUES (N'공구박스      ', N'공구함       ')
INSERT [dbo].[PLANET_BASE] ([planetName], [characterName]) VALUES (N'구구1       ', N'깜빡했다      ')
INSERT [dbo].[PLANET_BASE] ([planetName], [characterName]) VALUES (N'그냥별       ', N'오쿠샤       ')
INSERT [dbo].[PLANET_BASE] ([planetName], [characterName]) VALUES (N'기획서용행성    ', N'기획서용      ')
INSERT [dbo].[PLANET_BASE] ([planetName], [characterName]) VALUES (N'나메크성      ', N'장난감       ')
INSERT [dbo].[PLANET_BASE] ([planetName], [characterName]) VALUES (N'내 행성      ', N'ppppp     ')
INSERT [dbo].[PLANET_BASE] ([planetName], [characterName]) VALUES (N'내꺼        ', N'테스트용      ')
INSERT [dbo].[PLANET_BASE] ([planetName], [characterName]) VALUES (N'냐하항       ', N'test      ')
INSERT [dbo].[PLANET_BASE] ([planetName], [characterName]) VALUES (N'네르크란스     ', N'도라에몽      ')
INSERT [dbo].[PLANET_BASE] ([planetName], [characterName]) VALUES (N'달         ', N'가오리       ')
INSERT [dbo].[PLANET_BASE] ([planetName], [characterName]) VALUES (N'루나의 행성    ', N'루나        ')
INSERT [dbo].[PLANET_BASE] ([planetName], [characterName]) VALUES (N'망크별       ', N'망크        ')
INSERT [dbo].[PLANET_BASE] ([planetName], [characterName]) VALUES (N'미순        ', N'미순        ')
INSERT [dbo].[PLANET_BASE] ([planetName], [characterName]) VALUES (N'발         ', N'시발        ')
INSERT [dbo].[PLANET_BASE] ([planetName], [characterName]) VALUES (N'밥먹자       ', N'밥은먹고다니니   ')
INSERT [dbo].[PLANET_BASE] ([planetName], [characterName]) VALUES (N'별이        ', N'별이        ')
INSERT [dbo].[PLANET_BASE] ([planetName], [characterName]) VALUES (N'뽀잉        ', N'뿌잉        ')
INSERT [dbo].[PLANET_BASE] ([planetName], [characterName]) VALUES (N'뿡뿡이네      ', N'성기사뿌뿌뿡    ')
INSERT [dbo].[PLANET_BASE] ([planetName], [characterName]) VALUES (N'소녀시대      ', N'마성의유희열    ')
INSERT [dbo].[PLANET_BASE] ([planetName], [characterName]) VALUES (N'쉐끼루       ', N'신성일투      ')
INSERT [dbo].[PLANET_BASE] ([planetName], [characterName]) VALUES (N'쉬르벨       ', N'엄앵란       ')
INSERT [dbo].[PLANET_BASE] ([planetName], [characterName]) VALUES (N'스튜디오뮤트    ', N'휘플휘플      ')
INSERT [dbo].[PLANET_BASE] ([planetName], [characterName]) VALUES (N'아이유       ', N'유희열       ')
INSERT [dbo].[PLANET_BASE] ([planetName], [characterName]) VALUES (N'안녕하세요     ', N'와일드플래닛    ')
INSERT [dbo].[PLANET_BASE] ([planetName], [characterName]) VALUES (N'안드로메다     ', N'blackhole ')
INSERT [dbo].[PLANET_BASE] ([planetName], [characterName]) VALUES (N'앵란이는 어디에  ', N'신성일       ')
INSERT [dbo].[PLANET_BASE] ([planetName], [characterName]) VALUES (N'어이쿠야      ', N'어익쿠       ')
INSERT [dbo].[PLANET_BASE] ([planetName], [characterName]) VALUES (N'염소        ', N'qwer      ')
INSERT [dbo].[PLANET_BASE] ([planetName], [characterName]) VALUES (N'옴니        ', N'뽀오        ')
INSERT [dbo].[PLANET_BASE] ([planetName], [characterName]) VALUES (N'이런        ', N'아쭈구리      ')
INSERT [dbo].[PLANET_BASE] ([planetName], [characterName]) VALUES (N'제라드       ', N'제라드       ')
INSERT [dbo].[PLANET_BASE] ([planetName], [characterName]) VALUES (N'주인님차단하세요  ', N'님이그걸왜먹어여  ')
INSERT [dbo].[PLANET_BASE] ([planetName], [characterName]) VALUES (N'쥬신의별      ', N'기하        ')
INSERT [dbo].[PLANET_BASE] ([planetName], [characterName]) VALUES (N'지구~       ', N'후훗        ')
INSERT [dbo].[PLANET_BASE] ([planetName], [characterName]) VALUES (N'쨈성        ', N'째뮌        ')
INSERT [dbo].[PLANET_BASE] ([planetName], [characterName]) VALUES (N'카라        ', N'한승연       ')
INSERT [dbo].[PLANET_BASE] ([planetName], [characterName]) VALUES (N'쿡         ', N'곰발바닥      ')
INSERT [dbo].[PLANET_BASE] ([planetName], [characterName]) VALUES (N'타우농장      ', N'타우렌함유     ')
INSERT [dbo].[PLANET_BASE] ([planetName], [characterName]) VALUES (N'파란집       ', N'위대한 수령님   ')
INSERT [dbo].[PLANET_BASE] ([planetName], [characterName]) VALUES (N'팡팡게루      ', N'팡케루       ')
INSERT [dbo].[PLANET_BASE] ([planetName], [characterName]) VALUES (N'포더호드      ', N'다덤벼       ')
INSERT [dbo].[PLANET_BASE] ([planetName], [characterName]) VALUES (N'프레임워크     ', N'엔진        ')
INSERT [dbo].[PLANET_BASE] ([planetName], [characterName]) VALUES (N'피콜로제국     ', N'얄리몬       ')
INSERT [dbo].[PLANET_BASE] ([planetName], [characterName]) VALUES (N'행성이다      ', N'Luna      ')
INSERT [dbo].[PLANET_BASE] ([planetName], [characterName]) VALUES (N'혹성2b      ', N'야메        ')
INSERT [dbo].[PLANET_BASE] ([planetName], [characterName]) VALUES (N'황소별       ', N'나밥줘       ')
INSERT [dbo].[PLANET_BASE] ([planetName], [characterName]) VALUES (N'aa        ', N'aaa       ')
INSERT [dbo].[PLANET_BASE] ([planetName], [characterName]) VALUES (N'aaa       ', N'777       ')
INSERT [dbo].[PLANET_BASE] ([planetName], [characterName]) VALUES (N'adad      ', N'asdd      ')
INSERT [dbo].[PLANET_BASE] ([planetName], [characterName]) VALUES (N'bone      ', N'aka       ')
INSERT [dbo].[PLANET_BASE] ([planetName], [characterName]) VALUES (N'ddf       ', N'aaaaaf    ')
INSERT [dbo].[PLANET_BASE] ([planetName], [characterName]) VALUES (N'dwd       ', N'ddwee     ')
INSERT [dbo].[PLANET_BASE] ([planetName], [characterName]) VALUES (N'exxa      ', N'exxa      ')
INSERT [dbo].[PLANET_BASE] ([planetName], [characterName]) VALUES (N'fef       ', N'ds        ')
INSERT [dbo].[PLANET_BASE] ([planetName], [characterName]) VALUES (N'gfgfg     ', N'fdsfdsf   ')
INSERT [dbo].[PLANET_BASE] ([planetName], [characterName]) VALUES (N'Goat      ', N'푸르푸르      ')
INSERT [dbo].[PLANET_BASE] ([planetName], [characterName]) VALUES (N'MEMORY    ', N'KGDA      ')
INSERT [dbo].[PLANET_BASE] ([planetName], [characterName]) VALUES (N'moya      ', N'xkall     ')
INSERT [dbo].[PLANET_BASE] ([planetName], [characterName]) VALUES (N'ppp       ', N'ppp       ')
INSERT [dbo].[PLANET_BASE] ([planetName], [characterName]) VALUES (N'pppp의 행성  ', N'pppp      ')
INSERT [dbo].[PLANET_BASE] ([planetName], [characterName]) VALUES (N'puchon    ', N'mOok      ')
INSERT [dbo].[PLANET_BASE] ([planetName], [characterName]) VALUES (N'qqq       ', N'ff        ')
INSERT [dbo].[PLANET_BASE] ([planetName], [characterName]) VALUES (N'QWDQW     ', N'DREAMEXE  ')
INSERT [dbo].[PLANET_BASE] ([planetName], [characterName]) VALUES (N'qweqwe    ', N'asd       ')
INSERT [dbo].[PLANET_BASE] ([planetName], [characterName]) VALUES (N'SAM       ', N'sam       ')
INSERT [dbo].[PLANET_BASE] ([planetName], [characterName]) VALUES (N'ss        ', N'ss        ')
INSERT [dbo].[PLANET_BASE] ([planetName], [characterName]) VALUES (N'test1     ', N'test1     ')
INSERT [dbo].[PLANET_BASE] ([planetName], [characterName]) VALUES (N'test2     ', N'test2     ')
INSERT [dbo].[PLANET_BASE] ([planetName], [characterName]) VALUES (N'test3     ', N'test3     ')
INSERT [dbo].[PLANET_BASE] ([planetName], [characterName]) VALUES (N'testtest  ', N'수령님       ')
INSERT [dbo].[PLANET_BASE] ([planetName], [characterName]) VALUES (N'virtual   ', N'클스        ')
INSERT [dbo].[PLANET_BASE] ([planetName], [characterName]) VALUES (N'zxczx     ', N'dsscsd    ')
/****** Object:  StoredProcedure [dbo].[usp_ChangeStar]    Script Date: 10/29/2018 19:50:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
---------------------------
-- 객체이름 : dbo.usp_ChangeStar
-- 파라미터 : @pmName	NCHAR(10),	@pmSMoney	INT,	@pmRStar	INT
-- 제작자 : baboruri
-- 제작일 : 09-06-11
-- 변경일 : 
-- 내용 : risingStar -> starMoney 환전
-- 결과
-- 성공 Return : 0;
-- 실패 Return : 1;
---------------------------
CREATE PROCEDURE [dbo].[usp_ChangeStar]
	@pmName		NCHAR(10),
	@pmSMoney	INT,
	@pmRStar		INT
AS
	SET NOCOUNT ON
	
	UPDATE CHARACTER_BASE
	SET starMoney = @pmSMoney, risingStar = @pmRStar
	WHERE characterName = @pmName
	
	RETURN 0;
GO
/****** Object:  Table [dbo].[TRADE_OBJECT]    Script Date: 10/29/2018 19:50:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[TRADE_OBJECT](
	[tradeNum] [int] IDENTITY(1,1) NOT NULL,
	[characterName] [nchar](10) NOT NULL,
	[itemCode] [int] NOT NULL,
	[dealMode] [tinyint] NOT NULL,
	[buyTime] [smalldatetime] NOT NULL,
 CONSTRAINT [PK__TRADE_OBJECT] PRIMARY KEY CLUSTERED 
(
	[tradeNum] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
SET IDENTITY_INSERT [dbo].[TRADE_OBJECT] ON
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (27, N'엄앵란       ', 11011, 1, CAST(0x9C3E042F AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (28, N'엄앵란       ', 11021, 1, CAST(0x9C3E042F AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (29, N'엄앵란       ', 11042, 1, CAST(0x9C3E042F AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (30, N'엄앵란       ', 31001, 1, CAST(0x9C3E042F AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (31, N'엄앵란       ', 11042, 1, CAST(0x9C3E042F AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (32, N'엄앵란       ', 11042, 1, CAST(0x9C3E042F AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (33, N'엄앵란       ', 11011, 1, CAST(0x9C3E04D8 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (34, N'망크        ', 31001, 0, CAST(0x9C3F0356 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (35, N'망크        ', 17011, 0, CAST(0x9C3F0356 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (36, N'엄앵란       ', 11011, 1, CAST(0x9C3F03B4 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (37, N'마성의유희열    ', 11011, 1, CAST(0x9C3F04F8 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (38, N'마성의유희열    ', 11022, 1, CAST(0x9C3F04FF AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (39, N'마성의유희열    ', 16012, 1, CAST(0x9C3F04FF AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (40, N'마성의유희열    ', 14071, 1, CAST(0x9C3F0500 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (41, N'마성의유희열    ', 37001, 1, CAST(0x9C3F0500 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (42, N'수령님       ', 37001, 0, CAST(0x9C3F0525 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (43, N'수령님       ', 17011, 0, CAST(0x9C3F0525 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (44, N'마성의유희열    ', 11011, 1, CAST(0x9C3F052E AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (45, N'마성의유희열    ', 13011, 1, CAST(0x9C3F0530 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (46, N'마성의유희열    ', 11011, 1, CAST(0x9C3F0538 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (47, N'마성의유희열    ', 13011, 1, CAST(0x9C3F0538 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (48, N'마성의유희열    ', 11011, 1, CAST(0x9C3F053D AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (49, N'마성의유희열    ', 11021, 1, CAST(0x9C3F053D AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (50, N'마성의유희열    ', 11031, 1, CAST(0x9C3F053D AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (51, N'엄앵란       ', 12031, 1, CAST(0x9C3F0551 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (52, N'엄앵란       ', 12031, 1, CAST(0x9C3F0551 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (53, N'엄앵란       ', 12031, 1, CAST(0x9C3F0551 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (54, N'엄앵란       ', 12031, 1, CAST(0x9C3F0551 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (55, N'엄앵란       ', 12031, 1, CAST(0x9C3F0551 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (56, N'엄앵란       ', 12031, 1, CAST(0x9C3F0551 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (57, N'엄앵란       ', 12031, 1, CAST(0x9C3F0551 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (58, N'엄앵란       ', 13021, 1, CAST(0x9C3F0551 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (59, N'엄앵란       ', 13021, 1, CAST(0x9C3F0551 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (60, N'엄앵란       ', 13021, 1, CAST(0x9C3F0551 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (61, N'엄앵란       ', 14051, 1, CAST(0x9C3F0551 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (62, N'엄앵란       ', 14051, 1, CAST(0x9C3F0551 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (63, N'엄앵란       ', 14051, 1, CAST(0x9C3F0551 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (64, N'엄앵란       ', 14051, 1, CAST(0x9C3F0551 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (65, N'엄앵란       ', 14071, 1, CAST(0x9C3F0551 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (66, N'엄앵란       ', 14071, 1, CAST(0x9C3F0551 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (67, N'엄앵란       ', 16011, 1, CAST(0x9C3F0551 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (68, N'엄앵란       ', 16011, 1, CAST(0x9C3F0551 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (69, N'엄앵란       ', 16011, 1, CAST(0x9C3F0551 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (70, N'엄앵란       ', 16011, 1, CAST(0x9C3F0551 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (71, N'엄앵란       ', 16022, 1, CAST(0x9C3F0551 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (72, N'엄앵란       ', 16022, 1, CAST(0x9C3F0551 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (73, N'엄앵란       ', 16023, 1, CAST(0x9C3F0551 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (74, N'엄앵란       ', 16023, 1, CAST(0x9C3F0551 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (75, N'엄앵란       ', 16023, 1, CAST(0x9C3F0551 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (76, N'엄앵란       ', 16023, 1, CAST(0x9C3F0551 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (77, N'엄앵란       ', 16023, 1, CAST(0x9C3F0551 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (78, N'엄앵란       ', 11011, 1, CAST(0x9C3F0551 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (79, N'엄앵란       ', 17011, 1, CAST(0x9C3F0551 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (80, N'마성의유희열    ', 11011, 1, CAST(0x9C4002BE AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (81, N'마성의유희열    ', 11021, 1, CAST(0x9C4002BE AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (82, N'유희열       ', 37001, 0, CAST(0x9C4002C8 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (83, N'유희열       ', 17011, 0, CAST(0x9C4002C8 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (84, N'위대한 수령님   ', 31001, 0, CAST(0x9C4002D2 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (85, N'위대한 수령님   ', 17011, 0, CAST(0x9C4002D2 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (86, N'엄앵란       ', 11021, 1, CAST(0x9C4003B7 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (87, N'엄앵란       ', 32003, 1, CAST(0x9C4003B7 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (88, N'엄앵란       ', 33001, 1, CAST(0x9C4003B7 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (89, N'엄앵란       ', 11022, 1, CAST(0x9C4003B7 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (90, N'엄앵란       ', 11022, 1, CAST(0x9C4003B7 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (91, N'엄앵란       ', 11022, 1, CAST(0x9C4003B7 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (92, N'엄앵란       ', 11022, 1, CAST(0x9C4003B7 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (93, N'엄앵란       ', 11031, 1, CAST(0x9C4003B8 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (94, N'엄앵란       ', 11042, 1, CAST(0x9C4003B8 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (95, N'엄앵란       ', 11042, 1, CAST(0x9C4003B8 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (96, N'엄앵란       ', 12011, 1, CAST(0x9C4003B8 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (97, N'엄앵란       ', 12011, 1, CAST(0x9C4003B8 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (98, N'엄앵란       ', 12011, 1, CAST(0x9C4003B8 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (99, N'엄앵란       ', 13021, 1, CAST(0x9C4003B8 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (100, N'신성일투      ', 31001, 0, CAST(0x9C400402 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (101, N'신성일투      ', 17011, 0, CAST(0x9C400402 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (102, N'test1     ', 11022, 1, CAST(0x9C400558 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (103, N'유희열       ', 16012, 1, CAST(0x9C400582 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (104, N'유희열       ', 16012, 1, CAST(0x9C400582 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (105, N'유희열       ', 16012, 1, CAST(0x9C400582 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (106, N'유희열       ', 16012, 1, CAST(0x9C400582 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (107, N'유희열       ', 16012, 1, CAST(0x9C400582 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (108, N'유희열       ', 16012, 1, CAST(0x9C400582 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (109, N'유희열       ', 16012, 1, CAST(0x9C400582 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (110, N'유희열       ', 16012, 1, CAST(0x9C400582 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (111, N'유희열       ', 16012, 1, CAST(0x9C400582 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (112, N'유희열       ', 16012, 1, CAST(0x9C400583 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (113, N'유희열       ', 16012, 1, CAST(0x9C400583 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (114, N'유희열       ', 16012, 1, CAST(0x9C400583 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (115, N'유희열       ', 16012, 1, CAST(0x9C400583 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (116, N'유희열       ', 16012, 1, CAST(0x9C400583 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (117, N'유희열       ', 16012, 1, CAST(0x9C400583 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (118, N'유희열       ', 16012, 1, CAST(0x9C400583 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (119, N'유희열       ', 16012, 1, CAST(0x9C400583 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (120, N'test1     ', 11041, 1, CAST(0x9C41014B AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (121, N'test1     ', 12013, 1, CAST(0x9C41014B AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (122, N'성기사뿌뿌뿡    ', 32001, 0, CAST(0x9C410188 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (123, N'성기사뿌뿌뿡    ', 17011, 0, CAST(0x9C410188 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (124, N'터프가이      ', 32001, 0, CAST(0x9C41018B AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (125, N'터프가이      ', 17011, 0, CAST(0x9C41018B AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (126, N'엔진        ', 32003, 0, CAST(0x9C410195 AS SmallDateTime))
GO
print 'Processed 100 total records'
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (127, N'엔진        ', 17011, 0, CAST(0x9C410195 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (128, N'터프가이      ', 31001, 1, CAST(0x9C410196 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (129, N'터프가이      ', 31002, 1, CAST(0x9C410196 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (130, N'터프가이      ', 32002, 1, CAST(0x9C410196 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (131, N'터프가이      ', 32003, 1, CAST(0x9C410196 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (132, N'터프가이      ', 33001, 1, CAST(0x9C410196 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (133, N'터프가이      ', 33002, 1, CAST(0x9C410196 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (134, N'터프가이      ', 33003, 1, CAST(0x9C410196 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (135, N'터프가이      ', 34001, 1, CAST(0x9C410197 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (136, N'터프가이      ', 35001, 1, CAST(0x9C410197 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (137, N'터프가이      ', 35002, 1, CAST(0x9C410197 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (138, N'터프가이      ', 36001, 1, CAST(0x9C410197 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (139, N'터프가이      ', 37001, 1, CAST(0x9C410197 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (140, N'터프가이      ', 37002, 1, CAST(0x9C410197 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (141, N'터프가이      ', 38001, 1, CAST(0x9C410197 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (142, N'터프가이      ', 11011, 1, CAST(0x9C410197 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (143, N'터프가이      ', 11021, 1, CAST(0x9C410197 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (144, N'터프가이      ', 11022, 1, CAST(0x9C410197 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (145, N'터프가이      ', 11031, 1, CAST(0x9C410197 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (146, N'터프가이      ', 11041, 1, CAST(0x9C410197 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (147, N'터프가이      ', 11042, 1, CAST(0x9C410197 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (148, N'터프가이      ', 12011, 1, CAST(0x9C410197 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (149, N'터프가이      ', 12022, 1, CAST(0x9C410197 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (150, N'터프가이      ', 12032, 1, CAST(0x9C410197 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (151, N'터프가이      ', 12031, 1, CAST(0x9C410197 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (152, N'터프가이      ', 12033, 1, CAST(0x9C410197 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (153, N'터프가이      ', 13011, 1, CAST(0x9C410197 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (154, N'터프가이      ', 13021, 1, CAST(0x9C410197 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (155, N'터프가이      ', 14051, 1, CAST(0x9C410198 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (156, N'터프가이      ', 14071, 1, CAST(0x9C410198 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (157, N'터프가이      ', 16011, 1, CAST(0x9C410198 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (158, N'엔진        ', 16011, 1, CAST(0x9C410198 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (159, N'엔진        ', 11011, 1, CAST(0x9C410198 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (160, N'엔진        ', 17011, 1, CAST(0x9C410198 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (161, N'엔진        ', 11031, 1, CAST(0x9C410198 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (162, N'엔진        ', 12013, 1, CAST(0x9C410198 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (163, N'유희열       ', 16011, 1, CAST(0x9C4101D5 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (164, N'신성일       ', 37001, 0, CAST(0x9C4101D6 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (165, N'신성일       ', 17011, 0, CAST(0x9C4101D6 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (166, N'엄앵란       ', 33002, 1, CAST(0x9C41026A AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (167, N'엄앵란       ', 33003, 1, CAST(0x9C41026A AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (168, N'엄앵란       ', 34001, 1, CAST(0x9C41026A AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (169, N'엄앵란       ', 35001, 1, CAST(0x9C41026A AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (170, N'엄앵란       ', 35002, 1, CAST(0x9C41026A AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (171, N'엄앵란       ', 37001, 1, CAST(0x9C41026A AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (172, N'엄앵란       ', 12023, 1, CAST(0x9C41026A AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (173, N'test2     ', 11022, 1, CAST(0x9C410286 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (174, N'test2     ', 11041, 1, CAST(0x9C410286 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (175, N'test2     ', 37001, 1, CAST(0x9C410286 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (176, N'별이        ', 31002, 0, CAST(0x9C410324 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (177, N'별이        ', 17011, 0, CAST(0x9C410324 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (178, N'qwer      ', 36001, 0, CAST(0x9C410324 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (179, N'qwer      ', 17011, 0, CAST(0x9C410324 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (180, N'Luna      ', 37002, 0, CAST(0x9C410385 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (181, N'Luna      ', 17011, 0, CAST(0x9C410385 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (182, N'Luna      ', 33002, 1, CAST(0x9C410388 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (183, N'Luna      ', 35002, 1, CAST(0x9C410388 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (184, N'Luna      ', 36001, 1, CAST(0x9C410388 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (185, N'Luna      ', 11021, 1, CAST(0x9C410388 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (186, N'Luna      ', 12011, 1, CAST(0x9C410388 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (187, N'Luna      ', 14051, 1, CAST(0x9C410388 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (188, N'Luna      ', 14071, 1, CAST(0x9C410388 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (189, N'Luna      ', 16011, 1, CAST(0x9C410388 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (190, N'Luna      ', 16023, 1, CAST(0x9C410388 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (191, N'Luna      ', 11022, 1, CAST(0x9C410388 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (192, N'신성일투      ', 12031, 1, CAST(0x9C4203DB AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (193, N'Luna      ', 17011, 1, CAST(0x9C4203DF AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (194, N'Luna      ', 17011, 1, CAST(0x9C4203DF AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (195, N'제라드       ', 32001, 0, CAST(0x9C4302E7 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (196, N'제라드       ', 17011, 0, CAST(0x9C4302E7 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (197, N'별이        ', 12031, 1, CAST(0x9C44046A AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (198, N'별이        ', 14051, 1, CAST(0x9C44046A AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (199, N'별이        ', 14071, 1, CAST(0x9C44046A AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (200, N'별이        ', 14051, 1, CAST(0x9C44046B AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (201, N'아쭈구리      ', 31001, 0, CAST(0x9C450365 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (202, N'아쭈구리      ', 17011, 0, CAST(0x9C450365 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (203, N'Luna      ', 14041, 1, CAST(0x9C45041A AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (204, N'Luna      ', 17011, 1, CAST(0x9C45041A AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (205, N'Luna      ', 12011, 1, CAST(0x9C45041A AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (206, N'Luna      ', 12023, 1, CAST(0x9C45041A AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (207, N'타우렌함유     ', 32003, 0, CAST(0x9C46038E AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (208, N'타우렌함유     ', 17011, 0, CAST(0x9C46038E AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (209, N'유희열       ', 17011, 1, CAST(0x9C4704DF AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (210, N'망크        ', 17011, 1, CAST(0x9C48034E AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (211, N'망크        ', 17011, 1, CAST(0x9C480392 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (212, N'망크        ', 17011, 1, CAST(0x9C480393 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (213, N'망크        ', 12032, 1, CAST(0x9C49027D AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (214, N'망크        ', 16012, 1, CAST(0x9C49027F AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (215, N'망크        ', 16012, 1, CAST(0x9C49027F AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (216, N'기획서용      ', 37002, 0, CAST(0x9C4C03E5 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (217, N'기획서용      ', 17011, 0, CAST(0x9C4C03E5 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (218, N'엄앵란       ', 14071, 1, CAST(0x9C4D03A9 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (219, N'엄앵란       ', 14071, 1, CAST(0x9C4D03A9 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (220, N'엄앵란       ', 14071, 1, CAST(0x9C4D03A9 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (221, N'엄앵란       ', 14071, 1, CAST(0x9C4D03A9 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (222, N'엄앵란       ', 14071, 1, CAST(0x9C4D03A9 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (223, N'엄앵란       ', 14071, 1, CAST(0x9C4D03A9 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (224, N'엄앵란       ', 14071, 1, CAST(0x9C4D03A9 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (225, N'엄앵란       ', 14071, 1, CAST(0x9C4D03A9 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (226, N'엄앵란       ', 14071, 1, CAST(0x9C4D03A9 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (227, N'엄앵란       ', 14071, 1, CAST(0x9C4D03A9 AS SmallDateTime))
GO
print 'Processed 200 total records'
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (228, N'엄앵란       ', 14071, 1, CAST(0x9C4D03A9 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (229, N'엄앵란       ', 14071, 1, CAST(0x9C4D03A9 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (230, N'엄앵란       ', 14071, 1, CAST(0x9C4D03A9 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (231, N'엄앵란       ', 14071, 1, CAST(0x9C4D03A9 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (232, N'엄앵란       ', 14071, 1, CAST(0x9C4D03A9 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (233, N'엄앵란       ', 14071, 1, CAST(0x9C4D03A9 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (234, N'엄앵란       ', 14071, 1, CAST(0x9C4D03A9 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (235, N'엄앵란       ', 14071, 1, CAST(0x9C4D03A9 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (236, N'엄앵란       ', 14071, 1, CAST(0x9C4D03A9 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (237, N'엄앵란       ', 14071, 1, CAST(0x9C4D03A9 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (238, N'엄앵란       ', 14071, 1, CAST(0x9C4D03A9 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (239, N'엄앵란       ', 14071, 1, CAST(0x9C4D03A9 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (240, N'엄앵란       ', 14071, 1, CAST(0x9C4D03A9 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (241, N'엄앵란       ', 14051, 1, CAST(0x9C4D03A9 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (242, N'엄앵란       ', 14051, 1, CAST(0x9C4D03A9 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (243, N'엄앵란       ', 14051, 1, CAST(0x9C4D03A9 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (244, N'엄앵란       ', 14051, 1, CAST(0x9C4D03AA AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (245, N'엄앵란       ', 14051, 1, CAST(0x9C4D03AA AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (246, N'엄앵란       ', 14051, 1, CAST(0x9C4D03AA AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (247, N'엄앵란       ', 14051, 1, CAST(0x9C4D03AA AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (248, N'엄앵란       ', 14051, 1, CAST(0x9C4D03AA AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (249, N'엄앵란       ', 14051, 1, CAST(0x9C4D03AA AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (250, N'엄앵란       ', 14051, 1, CAST(0x9C4D03AA AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (251, N'님이그걸왜먹어여  ', 33001, 0, CAST(0x9C4D03AF AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (252, N'님이그걸왜먹어여  ', 17011, 0, CAST(0x9C4D03AF AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (253, N'Luna      ', 32002, 1, CAST(0x9C4D0416 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (254, N'Luna      ', 12011, 1, CAST(0x9C4D0416 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (255, N'터프가이      ', 14071, 1, CAST(0x9C4D04B5 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (256, N'터프가이      ', 14051, 1, CAST(0x9C4D04B5 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (257, N'터프가이      ', 14051, 1, CAST(0x9C4D04B5 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (258, N'터프가이      ', 14071, 1, CAST(0x9C4D04B5 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (259, N'터프가이      ', 14071, 1, CAST(0x9C4D04B5 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (260, N'터프가이      ', 14051, 1, CAST(0x9C4D04B5 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (261, N'aka       ', 32001, 0, CAST(0x9C4E005C AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (262, N'aka       ', 17011, 0, CAST(0x9C4E005C AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (263, N'777       ', 36001, 0, CAST(0x9C4E00A0 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (264, N'777       ', 17011, 0, CAST(0x9C4E00A0 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (265, N'터프가이      ', 11011, 1, CAST(0x9C4E038F AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (266, N'터프가이      ', 11011, 1, CAST(0x9C4E038F AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (267, N'터프가이      ', 11021, 1, CAST(0x9C4E038F AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (268, N'터프가이      ', 11022, 1, CAST(0x9C4E038F AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (269, N'터프가이      ', 11031, 1, CAST(0x9C4E038F AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (270, N'터프가이      ', 12013, 1, CAST(0x9C4E038F AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (271, N'터프가이      ', 13011, 1, CAST(0x9C4E038F AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (272, N'터프가이      ', 13021, 1, CAST(0x9C4E0390 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (273, N'터프가이      ', 13031, 1, CAST(0x9C4E0390 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (274, N'터프가이      ', 16011, 1, CAST(0x9C4E0390 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (275, N'터프가이      ', 16012, 1, CAST(0x9C4E0390 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (276, N'터프가이      ', 16011, 1, CAST(0x9C4E0390 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (277, N'터프가이      ', 16023, 1, CAST(0x9C4E0390 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (278, N'터프가이      ', 16022, 1, CAST(0x9C4E0390 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (279, N'터프가이      ', 11042, 1, CAST(0x9C4E039F AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (280, N'터프가이      ', 11041, 1, CAST(0x9C4E039F AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (281, N'test3     ', 31001, 0, CAST(0x9C4E03AA AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (282, N'test3     ', 17011, 0, CAST(0x9C4E03AA AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (283, N'터프가이      ', 11031, 1, CAST(0x9C4E03AD AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (284, N'터프가이      ', 12031, 1, CAST(0x9C4E03AD AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (285, N'터프가이      ', 16012, 1, CAST(0x9C4E03AD AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (286, N'터프가이      ', 16011, 1, CAST(0x9C4E03AD AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (287, N'터프가이      ', 16011, 1, CAST(0x9C4E03AD AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (288, N'test      ', 37002, 0, CAST(0x9C4E03D3 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (289, N'test      ', 17011, 0, CAST(0x9C4E03D3 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (290, N'나밥줘       ', 37002, 0, CAST(0x9C4F03E3 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (291, N'나밥줘       ', 17011, 0, CAST(0x9C4F03E3 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (292, N'어익쿠       ', 31001, 0, CAST(0x9C500276 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (293, N'어익쿠       ', 17011, 0, CAST(0x9C500276 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (294, N'장난감       ', 32003, 0, CAST(0x9C500287 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (295, N'장난감       ', 17011, 0, CAST(0x9C500287 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (296, N'mOok      ', 32003, 0, CAST(0x9C5002E7 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (297, N'mOok      ', 17011, 0, CAST(0x9C5002E7 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (298, N'오쿠샤       ', 36001, 0, CAST(0x9C5002F3 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (299, N'오쿠샤       ', 17011, 0, CAST(0x9C5002F3 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (300, N'DREAMEXE  ', 32003, 0, CAST(0x9C50030C AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (301, N'DREAMEXE  ', 17011, 0, CAST(0x9C50030C AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (302, N'다덤벼       ', 32003, 0, CAST(0x9C50030E AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (303, N'다덤벼       ', 17011, 0, CAST(0x9C50030E AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (304, N'깜빡했다      ', 32002, 0, CAST(0x9C50031A AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (305, N'깜빡했다      ', 17011, 0, CAST(0x9C50031A AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (306, N'야메        ', 31002, 0, CAST(0x9C50031B AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (307, N'야메        ', 17011, 0, CAST(0x9C50031B AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (308, N'밥은먹고다니니   ', 37002, 0, CAST(0x9C500321 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (309, N'밥은먹고다니니   ', 17011, 0, CAST(0x9C500321 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (310, N'blackhole ', 37002, 0, CAST(0x9C500326 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (311, N'blackhole ', 17011, 0, CAST(0x9C500326 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (312, N'공구함       ', 32003, 0, CAST(0x9C500337 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (313, N'공구함       ', 17011, 0, CAST(0x9C500337 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (314, N'째뮌        ', 31001, 0, CAST(0x9C50033C AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (315, N'째뮌        ', 17011, 0, CAST(0x9C50033C AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (316, N'aaa       ', 32001, 0, CAST(0x9C50034C AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (317, N'aaa       ', 17011, 0, CAST(0x9C50034C AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (318, N'가오리       ', 33001, 0, CAST(0x9C50034D AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (319, N'가오리       ', 17011, 0, CAST(0x9C50034D AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (320, N'다덤벼       ', 12011, 1, CAST(0x9C500353 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (321, N'후훗        ', 31001, 0, CAST(0x9C50035F AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (322, N'후훗        ', 17011, 0, CAST(0x9C50035F AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (323, N'후훗        ', 31002, 1, CAST(0x9C500377 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (324, N'후훗        ', 11021, 1, CAST(0x9C500377 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (325, N'후훗        ', 11022, 1, CAST(0x9C500377 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (326, N'후훗        ', 33001, 1, CAST(0x9C500377 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (327, N'도라에몽      ', 32003, 0, CAST(0x9C50037A AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (328, N'도라에몽      ', 17011, 0, CAST(0x9C50037A AS SmallDateTime))
GO
print 'Processed 300 total records'
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (329, N'ff        ', 32003, 0, CAST(0x9C5003BA AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (330, N'ff        ', 17011, 0, CAST(0x9C5003BA AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (331, N'asdf      ', 32001, 0, CAST(0x9C5003CD AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (332, N'asdf      ', 17011, 0, CAST(0x9C5003CD AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (333, N'fdsfdsf   ', 31002, 0, CAST(0x9C5003CE AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (334, N'fdsfdsf   ', 17011, 0, CAST(0x9C5003CE AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (335, N'5555      ', 33001, 0, CAST(0x9C5003FE AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (336, N'5555      ', 17011, 0, CAST(0x9C5003FE AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (337, N'dsscsd    ', 37001, 0, CAST(0x9C500415 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (338, N'dsscsd    ', 17011, 0, CAST(0x9C500415 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (339, N'뿌잉        ', 32003, 0, CAST(0x9C50042C AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (340, N'뿌잉        ', 17011, 0, CAST(0x9C50042C AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (341, N'기하        ', 31001, 0, CAST(0x9C500434 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (342, N'기하        ', 17011, 0, CAST(0x9C500434 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (343, N'aaaaaf    ', 31001, 0, CAST(0x9C50043E AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (344, N'aaaaaf    ', 17011, 0, CAST(0x9C50043E AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (345, N'휘플휘플      ', 38002, 0, CAST(0x9C50045B AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (346, N'휘플휘플      ', 17011, 0, CAST(0x9C50045B AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (347, N'뽀오        ', 32003, 0, CAST(0x9C50045D AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (348, N'뽀오        ', 17011, 0, CAST(0x9C50045D AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (349, N'팡케루       ', 37002, 0, CAST(0x9C50045E AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (350, N'팡케루       ', 17011, 0, CAST(0x9C50045E AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (351, N'휘플휘플      ', 12031, 1, CAST(0x9C50045E AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (352, N'휘플휘플      ', 11011, 1, CAST(0x9C50045F AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (353, N'xkall     ', 37001, 0, CAST(0x9C50049D AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (354, N'xkall     ', 17011, 0, CAST(0x9C50049D AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (355, N'푸르푸르      ', 31002, 0, CAST(0x9C5004AB AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (356, N'푸르푸르      ', 17011, 0, CAST(0x9C5004AB AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (357, N'별이        ', 11042, 1, CAST(0x9C5004B0 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (358, N'별이        ', 11041, 1, CAST(0x9C5004B0 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (359, N'별이        ', 12032, 1, CAST(0x9C5004B0 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (360, N'별이        ', 11031, 1, CAST(0x9C5004B0 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (361, N'666       ', 33003, 0, CAST(0x9C50052E AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (362, N'666       ', 17011, 0, CAST(0x9C50052E AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (363, N'dma..     ', 38002, 0, CAST(0x9C51054F AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (364, N'dma..     ', 17011, 0, CAST(0x9C51054F AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (365, N'dma..     ', 32002, 1, CAST(0x9C510552 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (366, N'dma..     ', 11031, 1, CAST(0x9C510552 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (367, N'ds        ', 32003, 0, CAST(0x9C520329 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (368, N'ds        ', 17011, 0, CAST(0x9C520329 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (369, N'ds        ', 11022, 1, CAST(0x9C52032C AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (370, N'와일드플래닛    ', 37002, 0, CAST(0x9C55026F AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (371, N'와일드플래닛    ', 17011, 0, CAST(0x9C55026F AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (372, N'별이        ', 32001, 1, CAST(0x9C55028A AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (373, N'와일드플래닛    ', 11031, 1, CAST(0x9C55028A AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (374, N'와일드플래닛    ', 12033, 1, CAST(0x9C55028A AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (375, N'와일드플래닛    ', 16012, 1, CAST(0x9C55028A AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (376, N'별이        ', 11042, 1, CAST(0x9C550298 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (377, N'별이        ', 11041, 1, CAST(0x9C550298 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (378, N'Luna      ', 11011, 1, CAST(0x9C5502E7 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (379, N'Luna      ', 11031, 1, CAST(0x9C5502E7 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (380, N'Luna      ', 11031, 1, CAST(0x9C5502E7 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (381, N'Luna      ', 11031, 1, CAST(0x9C5502E7 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (382, N'Luna      ', 11031, 1, CAST(0x9C5502E7 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (383, N'Luna      ', 12021, 1, CAST(0x9C5502E7 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (384, N'Luna      ', 12033, 1, CAST(0x9C5502E7 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (385, N'Luna      ', 12033, 1, CAST(0x9C5502E7 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (386, N'Luna      ', 12033, 1, CAST(0x9C5502E7 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (387, N'Luna      ', 12033, 1, CAST(0x9C5502E7 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (388, N'Luna      ', 12033, 1, CAST(0x9C5502E7 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (389, N'Luna      ', 16012, 1, CAST(0x9C5502E8 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (390, N'Luna      ', 16012, 1, CAST(0x9C5502E8 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (391, N'Luna      ', 14071, 1, CAST(0x9C5502E8 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (392, N'Luna      ', 14051, 1, CAST(0x9C5502E8 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (393, N'Luna      ', 16012, 1, CAST(0x9C5502E8 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (394, N'Luna      ', 16023, 1, CAST(0x9C5502E8 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (395, N'Luna      ', 16023, 1, CAST(0x9C5502E8 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (396, N'Luna      ', 16023, 1, CAST(0x9C5502E8 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (397, N'Luna      ', 16023, 1, CAST(0x9C5502E8 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (398, N'Luna      ', 16012, 1, CAST(0x9C5502EA AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (399, N'Luna      ', 16012, 1, CAST(0x9C5502EB AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (400, N'Luna      ', 16012, 1, CAST(0x9C5502EB AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (401, N'Luna      ', 16012, 1, CAST(0x9C5502EB AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (402, N'Luna      ', 12022, 1, CAST(0x9C5502EF AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (403, N'Luna      ', 12022, 1, CAST(0x9C5502EF AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (404, N'Luna      ', 12023, 1, CAST(0x9C5502EF AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (405, N'Luna      ', 12023, 1, CAST(0x9C5502EF AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (406, N'테스트용      ', 32003, 0, CAST(0x9C5502FC AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (407, N'테스트용      ', 17011, 0, CAST(0x9C5502FC AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (408, N'asd       ', 32002, 0, CAST(0x9C550381 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (409, N'asd       ', 17011, 0, CAST(0x9C550381 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (410, N'Luna      ', 35001, 1, CAST(0x9C550383 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (411, N'Luna      ', 11031, 1, CAST(0x9C550383 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (412, N'Luna      ', 11022, 1, CAST(0x9C550383 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (413, N'sam       ', 31001, 0, CAST(0x9C5504DE AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (414, N'sam       ', 17011, 0, CAST(0x9C5504DE AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (415, N'ss        ', 32003, 0, CAST(0x9C5604A2 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (416, N'ss        ', 17011, 0, CAST(0x9C5604A2 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (417, N'루나        ', 32001, 0, CAST(0x9C5E0372 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (418, N'루나        ', 17011, 0, CAST(0x9C5E0372 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (419, N'한승연       ', 37002, 0, CAST(0x9C6102B3 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (420, N'한승연       ', 17011, 0, CAST(0x9C6102B3 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (421, N'한승연       ', 31001, 1, CAST(0x9C6102B6 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (422, N'한승연       ', 11011, 1, CAST(0x9C6102B6 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (423, N'얄리몬       ', 32001, 0, CAST(0x9C610320 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (424, N'얄리몬       ', 17011, 0, CAST(0x9C610320 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (425, N'터프가이      ', 12022, 1, CAST(0x9C62027C AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (426, N'터프가이      ', 12022, 1, CAST(0x9C62027C AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (427, N'터프가이      ', 12033, 1, CAST(0x9C62027C AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (428, N'1         ', 32003, 0, CAST(0x9C650062 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (429, N'1         ', 17011, 0, CAST(0x9C650062 AS SmallDateTime))
GO
print 'Processed 400 total records'
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (430, N'ppp       ', 37001, 0, CAST(0x9C6B02F2 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (431, N'ppp       ', 17011, 0, CAST(0x9C6B02F2 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (432, N'ppp       ', 33001, 1, CAST(0x9C6B02F7 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (433, N'ppp       ', 33002, 1, CAST(0x9C6B02F7 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (434, N'ppp       ', 11042, 1, CAST(0x9C6B02F7 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (435, N'exxa      ', 32002, 1, CAST(0x9C6C022E AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (436, N'exxa      ', 16011, 1, CAST(0x9C6C022F AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (437, N'exxa      ', 16011, 1, CAST(0x9C6C022F AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (438, N'exxa      ', 16011, 1, CAST(0x9C6C022F AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (439, N'exxa      ', 11011, 1, CAST(0x9C6C022F AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (440, N'exxa      ', 11011, 1, CAST(0x9C6C022F AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (441, N'exxa      ', 11011, 1, CAST(0x9C6C022F AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (442, N'pppp      ', 32002, 0, CAST(0x9C6C0246 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (443, N'pppp      ', 17011, 0, CAST(0x9C6C0246 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (444, N'exxa      ', 33003, 1, CAST(0x9C6C0248 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (445, N'exxa      ', 11042, 1, CAST(0x9C6C0248 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (446, N'exxa      ', 12013, 1, CAST(0x9C6C0248 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (447, N'ppppp     ', 34001, 0, CAST(0x9C6D03CA AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (448, N'ppppp     ', 17011, 0, CAST(0x9C6D03CA AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (449, N'exxa      ', 32001, 1, CAST(0x9C6D03CC AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (450, N'exxa      ', 14071, 1, CAST(0x9C6D03CC AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (451, N'exxa      ', 14051, 1, CAST(0x9C6D03CC AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (452, N'미순        ', 33001, 0, CAST(0x9C6E0409 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (453, N'미순        ', 17011, 0, CAST(0x9C6E0409 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (454, N'별이        ', 33001, 1, CAST(0x9C6E040B AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (455, N'별이        ', 12031, 1, CAST(0x9C6E040B AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (456, N'별이        ', 13011, 1, CAST(0x9C6E040B AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (457, N'KGDA      ', 31001, 0, CAST(0x9C73023F AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (458, N'KGDA      ', 17011, 0, CAST(0x9C73023F AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (459, N'KGDA      ', 11022, 1, CAST(0x9C730248 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (460, N'클스        ', 37002, 0, CAST(0x9C7C0432 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (461, N'클스        ', 17011, 0, CAST(0x9C7C0432 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (462, N'asdd      ', 31001, 0, CAST(0x9CA202DD AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (463, N'asdd      ', 17011, 0, CAST(0x9CA202DD AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (464, N'ddwee     ', 31001, 0, CAST(0x9CA202E1 AS SmallDateTime))
INSERT [dbo].[TRADE_OBJECT] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (465, N'ddwee     ', 17011, 0, CAST(0x9CA202E1 AS SmallDateTime))
SET IDENTITY_INSERT [dbo].[TRADE_OBJECT] OFF
/****** Object:  Table [dbo].[TRADE_AVATAR]    Script Date: 10/29/2018 19:50:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[TRADE_AVATAR](
	[tradeNum] [int] IDENTITY(1,1) NOT NULL,
	[characterName] [nchar](10) NOT NULL,
	[itemCode] [int] NOT NULL,
	[dealMode] [tinyint] NOT NULL,
	[buyTime] [smalldatetime] NOT NULL,
 CONSTRAINT [PK__TRADE_AVATAR] PRIMARY KEY CLUSTERED 
(
	[tradeNum] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
SET IDENTITY_INSERT [dbo].[TRADE_AVATAR] ON
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (1, N'시발        ', 70001, 0, CAST(0x9C3C034F AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (2, N'시발        ', 50011, 0, CAST(0x9C3C034F AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (3, N'exxa      ', 70001, 0, CAST(0x9C3C0505 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (4, N'exxa      ', 50011, 0, CAST(0x9C3C0505 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (5, N'마성의유희열    ', 70001, 0, CAST(0x9C3C0521 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (6, N'마성의유희열    ', 50011, 0, CAST(0x9C3C0521 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (7, N'엄앵란       ', 70002, 0, CAST(0x9C3C0532 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (8, N'엄앵란       ', 50011, 0, CAST(0x9C3C0532 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (9, N'test1     ', 70002, 0, CAST(0x9C3D0345 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (10, N'test1     ', 50012, 0, CAST(0x9C3D0345 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (11, N'test2     ', 70002, 0, CAST(0x9C3D0346 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (12, N'test2     ', 50012, 0, CAST(0x9C3D0346 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (13, N'곰발바닥      ', 70002, 0, CAST(0x9C3D0486 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (14, N'곰발바닥      ', 50011, 0, CAST(0x9C3D0486 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (15, N'엄앵란       ', 40001, 1, CAST(0x9C3D050F AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (16, N'엄앵란       ', 40002, 1, CAST(0x9C3D050F AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (17, N'엄앵란       ', 50002, 1, CAST(0x9C3D051F AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (18, N'엄앵란       ', 50004, 1, CAST(0x9C3D051F AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (19, N'엄앵란       ', 60002, 1, CAST(0x9C3D051F AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (20, N'엄앵란       ', 60005, 1, CAST(0x9C3D051F AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (21, N'엄앵란       ', 70001, 1, CAST(0x9C3D051F AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (22, N'엄앵란       ', 50001, 1, CAST(0x9C3E0287 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (23, N'엄앵란       ', 50002, 1, CAST(0x9C3E0287 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (24, N'엄앵란       ', 50003, 1, CAST(0x9C3E0288 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (25, N'엄앵란       ', 60003, 1, CAST(0x9C3E0288 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (26, N'엄앵란       ', 60005, 1, CAST(0x9C3E028A AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (27, N'엄앵란       ', 60001, 1, CAST(0x9C3E028A AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (28, N'엄앵란       ', 70001, 1, CAST(0x9C3E028A AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (29, N'엄앵란       ', 60002, 1, CAST(0x9C3E029C AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (30, N'엄앵란       ', 60006, 1, CAST(0x9C3E029D AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (31, N'엄앵란       ', 50012, 1, CAST(0x9C3E029D AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (32, N'엄앵란       ', 60008, 1, CAST(0x9C3E02DF AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (33, N'엄앵란       ', 60004, 1, CAST(0x9C3E0415 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (34, N'엄앵란       ', 60007, 1, CAST(0x9C3E0416 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (35, N'test1     ', 70002, 1, CAST(0x9C3E0419 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (36, N'test1     ', 40002, 1, CAST(0x9C3E0423 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (37, N'test1     ', 60002, 1, CAST(0x9C3E0423 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (38, N'test1     ', 60003, 1, CAST(0x9C3E0423 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (39, N'test1     ', 50004, 1, CAST(0x9C3E0423 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (40, N'test1     ', 50002, 1, CAST(0x9C3E0424 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (41, N'test1     ', 60001, 1, CAST(0x9C3E0462 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (42, N'test1     ', 50001, 1, CAST(0x9C3E0462 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (43, N'exxa      ', 70002, 1, CAST(0x9C3E0471 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (44, N'exxa      ', 50002, 1, CAST(0x9C3E0471 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (45, N'exxa      ', 40002, 1, CAST(0x9C3E0471 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (46, N'zzz       ', 70001, 0, CAST(0x9C3F02CF AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (47, N'zzz       ', 50012, 0, CAST(0x9C3F02CF AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (48, N'select    ', 70001, 0, CAST(0x9C3F02EC AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (49, N'select    ', 50003, 0, CAST(0x9C3F02EC AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (50, N'test2     ', 70001, 1, CAST(0x9C3F0305 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (51, N'test2     ', 40001, 1, CAST(0x9C3F0307 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (52, N'test2     ', 60001, 1, CAST(0x9C3F0307 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (53, N'수령님       ', 70001, 0, CAST(0x9C3F030A AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (54, N'수령님       ', 50004, 0, CAST(0x9C3F030A AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (55, N'망크        ', 70002, 0, CAST(0x9C3F0355 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (56, N'망크        ', 50001, 0, CAST(0x9C3F0355 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (57, N'엄앵란       ', 50004, 1, CAST(0x9C3F03B4 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (58, N'유희열       ', 70001, 0, CAST(0x9C4002C7 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (59, N'유희열       ', 50001, 0, CAST(0x9C4002C7 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (60, N'신성일       ', 70001, 0, CAST(0x9C4002CB AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (61, N'신성일       ', 50002, 0, CAST(0x9C4002CB AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (62, N'위대한 수령님   ', 70001, 0, CAST(0x9C4002D2 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (63, N'위대한 수령님   ', 50011, 0, CAST(0x9C4002D2 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (64, N'신성일투      ', 70002, 0, CAST(0x9C400402 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (65, N'신성일투      ', 50003, 0, CAST(0x9C400402 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (66, N'유희열       ', 40001, 1, CAST(0x9C400581 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (67, N'유희열       ', 60001, 1, CAST(0x9C400581 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (68, N'유희열       ', 60002, 1, CAST(0x9C400581 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (69, N'유희열       ', 60003, 1, CAST(0x9C400582 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (70, N'유희열       ', 60004, 1, CAST(0x9C400582 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (71, N'유희열       ', 60005, 1, CAST(0x9C400582 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (72, N'유희열       ', 60006, 1, CAST(0x9C400582 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (73, N'유희열       ', 60007, 1, CAST(0x9C400582 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (74, N'유희열       ', 60008, 1, CAST(0x9C400582 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (75, N'유희열       ', 50011, 1, CAST(0x9C400582 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (76, N'유희열       ', 50012, 1, CAST(0x9C400582 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (77, N'유희열       ', 50002, 1, CAST(0x9C400582 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (78, N'유희열       ', 50003, 1, CAST(0x9C400582 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (79, N'유희열       ', 50004, 1, CAST(0x9C400582 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (80, N'유희열       ', 40002, 1, CAST(0x9C400582 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (81, N'유희열       ', 70002, 1, CAST(0x9C400582 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (82, N'test2     ', 40002, 1, CAST(0x9C41003B AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (83, N'test2     ', 60002, 1, CAST(0x9C41003B AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (84, N'test2     ', 50001, 1, CAST(0x9C41003B AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (85, N'test2     ', 60006, 1, CAST(0x9C410175 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (86, N'test2     ', 50011, 1, CAST(0x9C410175 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (87, N'성기사뿌뿌뿡    ', 70002, 0, CAST(0x9C410188 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (88, N'성기사뿌뿌뿡    ', 50001, 0, CAST(0x9C410188 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (89, N'터프가이      ', 70001, 0, CAST(0x9C41018B AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (90, N'터프가이      ', 50012, 0, CAST(0x9C41018B AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (91, N'터프가이      ', 70002, 1, CAST(0x9C410195 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (92, N'터프가이      ', 40002, 1, CAST(0x9C410195 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (93, N'터프가이      ', 40001, 1, CAST(0x9C410195 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (94, N'터프가이      ', 60002, 1, CAST(0x9C410195 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (95, N'터프가이      ', 60003, 1, CAST(0x9C410195 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (96, N'엔진        ', 70002, 0, CAST(0x9C410195 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (97, N'엔진        ', 50004, 0, CAST(0x9C410195 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (98, N'터프가이      ', 60004, 1, CAST(0x9C410196 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (99, N'터프가이      ', 60005, 1, CAST(0x9C410196 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (100, N'터프가이      ', 60006, 1, CAST(0x9C410196 AS SmallDateTime))
GO
print 'Processed 100 total records'
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (101, N'터프가이      ', 60007, 1, CAST(0x9C410196 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (102, N'터프가이      ', 60008, 1, CAST(0x9C410196 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (103, N'터프가이      ', 60001, 1, CAST(0x9C410196 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (104, N'터프가이      ', 50011, 1, CAST(0x9C410196 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (105, N'터프가이      ', 50001, 1, CAST(0x9C410196 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (106, N'터프가이      ', 50002, 1, CAST(0x9C410196 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (107, N'터프가이      ', 50003, 1, CAST(0x9C410196 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (108, N'Luna      ', 70001, 0, CAST(0x9C410197 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (109, N'Luna      ', 50002, 0, CAST(0x9C410197 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (110, N'엔진        ', 40002, 1, CAST(0x9C41019A AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (111, N'엔진        ', 50011, 1, CAST(0x9C41019A AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (112, N'엔진        ', 60007, 1, CAST(0x9C41019A AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (113, N'터프가이      ', 50004, 1, CAST(0x9C41019D AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (114, N'test1     ', 60006, 1, CAST(0x9C4101D4 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (115, N'test2     ', 50004, 1, CAST(0x9C410286 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (116, N'test2     ', 50002, 1, CAST(0x9C410296 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (117, N'test2     ', 60004, 1, CAST(0x9C410297 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (118, N'test2     ', 60007, 1, CAST(0x9C410297 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (119, N'test2     ', 60008, 1, CAST(0x9C410297 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (120, N'신성일투      ', 70001, 1, CAST(0x9C410321 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (121, N'신성일투      ', 60002, 1, CAST(0x9C410321 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (122, N'신성일투      ', 50012, 1, CAST(0x9C410321 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (123, N'신성일투      ', 50002, 1, CAST(0x9C410321 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (124, N'신성일투      ', 60005, 1, CAST(0x9C410321 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (125, N'qwer      ', 70001, 0, CAST(0x9C410323 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (126, N'qwer      ', 50012, 0, CAST(0x9C410323 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (127, N'별이        ', 70001, 0, CAST(0x9C410323 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (128, N'별이        ', 50011, 0, CAST(0x9C410323 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (129, N'test1     ', 40001, 1, CAST(0x9C410361 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (130, N'test1     ', 60004, 1, CAST(0x9C410361 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (131, N'Luna      ', 70002, 1, CAST(0x9C410387 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (132, N'Luna      ', 40001, 1, CAST(0x9C410387 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (133, N'Luna      ', 40002, 1, CAST(0x9C410387 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (134, N'Luna      ', 60005, 1, CAST(0x9C410387 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (135, N'Luna      ', 60006, 1, CAST(0x9C410387 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (136, N'Luna      ', 60007, 1, CAST(0x9C410387 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (137, N'Luna      ', 60008, 1, CAST(0x9C410387 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (138, N'Luna      ', 60001, 1, CAST(0x9C410387 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (139, N'Luna      ', 50003, 1, CAST(0x9C410388 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (140, N'Luna      ', 50004, 1, CAST(0x9C410388 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (141, N'Luna      ', 50011, 1, CAST(0x9C410388 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (142, N'Luna      ', 50001, 1, CAST(0x9C410388 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (143, N'제라드       ', 70001, 0, CAST(0x9C4302E7 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (144, N'제라드       ', 50002, 0, CAST(0x9C4302E7 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (145, N'판타지 스타    ', 70001, 0, CAST(0x9C440347 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (146, N'판타지 스타    ', 50002, 0, CAST(0x9C440347 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (147, N'젠장        ', 70002, 0, CAST(0x9C440402 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (148, N'젠장        ', 50001, 0, CAST(0x9C440402 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (149, N'아쭈구리      ', 70001, 0, CAST(0x9C450364 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (150, N'아쭈구리      ', 50002, 0, CAST(0x9C450364 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (151, N'신성일투      ', 60001, 1, CAST(0x9C4503AF AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (152, N'신성일투      ', 60003, 1, CAST(0x9C4503AF AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (153, N'신성일투      ', 60004, 1, CAST(0x9C4503AF AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (154, N'신성일투      ', 60006, 1, CAST(0x9C4503AF AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (155, N'신성일투      ', 60007, 1, CAST(0x9C4503AF AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (156, N'신성일투      ', 60008, 1, CAST(0x9C4503AF AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (157, N'신성일투      ', 50011, 1, CAST(0x9C4503B0 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (158, N'신성일투      ', 50004, 1, CAST(0x9C4503B0 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (159, N'신성일투      ', 50001, 1, CAST(0x9C4503B0 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (160, N'신성일투      ', 40002, 1, CAST(0x9C4503B8 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (161, N'신성일투      ', 40001, 1, CAST(0x9C4503B8 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (162, N'타우렌함유     ', 70002, 0, CAST(0x9C46038C AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (163, N'타우렌함유     ', 50001, 0, CAST(0x9C46038C AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (164, N'기획서용      ', 70001, 0, CAST(0x9C4C03E4 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (165, N'기획서용      ', 50002, 0, CAST(0x9C4C03E4 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (166, N'님이그걸왜먹어여  ', 70002, 0, CAST(0x9C4D03AF AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (167, N'님이그걸왜먹어여  ', 50003, 0, CAST(0x9C4D03AF AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (168, N'Luna      ', 60003, 1, CAST(0x9C4D0416 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (169, N'aka       ', 70002, 0, CAST(0x9C4E005C AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (170, N'aka       ', 50002, 0, CAST(0x9C4E005C AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (171, N'777       ', 70002, 0, CAST(0x9C4E009F AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (172, N'777       ', 50003, 0, CAST(0x9C4E009F AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (173, N'test3     ', 70002, 0, CAST(0x9C4E03AA AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (174, N'test3     ', 50002, 0, CAST(0x9C4E03AA AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (175, N'test      ', 70002, 0, CAST(0x9C4E03D2 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (176, N'test      ', 50002, 0, CAST(0x9C4E03D2 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (177, N'별이        ', 40002, 1, CAST(0x9C4E0410 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (178, N'나밥줘       ', 70001, 0, CAST(0x9C4F03E2 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (179, N'나밥줘       ', 50004, 0, CAST(0x9C4F03E2 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (180, N'나밥줘       ', 60001, 1, CAST(0x9C4F0517 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (181, N'나밥줘       ', 40001, 1, CAST(0x9C4F0517 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (182, N'어익쿠       ', 70002, 0, CAST(0x9C500275 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (183, N'어익쿠       ', 50002, 0, CAST(0x9C500275 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (184, N'어익쿠       ', 60001, 1, CAST(0x9C50027A AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (185, N'장난감       ', 70001, 0, CAST(0x9C500287 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (186, N'장난감       ', 50004, 0, CAST(0x9C500287 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (187, N'dddd      ', 70002, 0, CAST(0x9C5002D6 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (188, N'dddd      ', 50002, 0, CAST(0x9C5002D6 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (189, N'mOok      ', 70002, 0, CAST(0x9C5002E4 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (190, N'mOok      ', 50012, 0, CAST(0x9C5002E4 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (191, N'mOok      ', 40002, 1, CAST(0x9C5002E8 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (192, N'mOok      ', 60006, 1, CAST(0x9C5002E8 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (193, N'오쿠샤       ', 70001, 0, CAST(0x9C5002F3 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (194, N'오쿠샤       ', 50011, 0, CAST(0x9C5002F3 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (195, N'DREAMEXE  ', 70001, 0, CAST(0x9C50030C AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (196, N'DREAMEXE  ', 50003, 0, CAST(0x9C50030C AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (197, N'다덤벼       ', 70002, 0, CAST(0x9C50030D AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (198, N'다덤벼       ', 50002, 0, CAST(0x9C50030D AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (199, N'깜빡했다      ', 70002, 0, CAST(0x9C50031A AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (200, N'깜빡했다      ', 50011, 0, CAST(0x9C50031A AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (201, N'야메        ', 70001, 0, CAST(0x9C50031A AS SmallDateTime))
GO
print 'Processed 200 total records'
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (202, N'야메        ', 50004, 0, CAST(0x9C50031A AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (203, N'밥은먹고다니니   ', 70002, 0, CAST(0x9C500321 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (204, N'밥은먹고다니니   ', 50011, 0, CAST(0x9C500321 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (205, N'blackhole ', 70001, 0, CAST(0x9C500325 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (206, N'blackhole ', 50012, 0, CAST(0x9C500325 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (207, N'공구함       ', 70001, 0, CAST(0x9C500337 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (208, N'공구함       ', 50011, 0, CAST(0x9C500337 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (209, N'째뮌        ', 70001, 0, CAST(0x9C50033C AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (210, N'째뮌        ', 50003, 0, CAST(0x9C50033C AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (211, N'aaa       ', 70001, 0, CAST(0x9C50034C AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (212, N'aaa       ', 50001, 0, CAST(0x9C50034C AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (213, N'가오리       ', 70001, 0, CAST(0x9C50034D AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (214, N'가오리       ', 50011, 0, CAST(0x9C50034D AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (215, N'공구함       ', 40001, 1, CAST(0x9C500350 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (216, N'다덤벼       ', 40001, 1, CAST(0x9C500353 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (217, N'다덤벼       ', 60001, 1, CAST(0x9C500353 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (218, N'다덤벼       ', 50012, 1, CAST(0x9C500353 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (219, N'후훗        ', 70002, 0, CAST(0x9C50035F AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (220, N'후훗        ', 50011, 0, CAST(0x9C50035F AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (221, N'후훗        ', 40001, 1, CAST(0x9C500376 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (222, N'후훗        ', 60001, 1, CAST(0x9C500377 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (223, N'후훗        ', 50012, 1, CAST(0x9C500377 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (224, N'도라에몽      ', 70002, 0, CAST(0x9C50037A AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (225, N'도라에몽      ', 50001, 0, CAST(0x9C50037A AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (226, N'ff        ', 70001, 0, CAST(0x9C5003B9 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (227, N'ff        ', 50004, 0, CAST(0x9C5003B9 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (228, N'asdf      ', 70001, 0, CAST(0x9C5003CD AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (229, N'asdf      ', 50002, 0, CAST(0x9C5003CD AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (230, N'fdsfdsf   ', 70002, 0, CAST(0x9C5003CD AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (231, N'fdsfdsf   ', 50001, 0, CAST(0x9C5003CD AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (232, N'5555      ', 70002, 0, CAST(0x9C5003FD AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (233, N'5555      ', 50001, 0, CAST(0x9C5003FD AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (234, N'dsscsd    ', 70002, 0, CAST(0x9C500415 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (235, N'dsscsd    ', 50002, 0, CAST(0x9C500415 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (236, N'뿌잉        ', 70002, 0, CAST(0x9C50042C AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (237, N'뿌잉        ', 50004, 0, CAST(0x9C50042C AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (238, N'기하        ', 70001, 0, CAST(0x9C500434 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (239, N'기하        ', 50012, 0, CAST(0x9C500434 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (240, N'aaaaaf    ', 70001, 0, CAST(0x9C50043E AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (241, N'aaaaaf    ', 50003, 0, CAST(0x9C50043E AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (242, N'휘플휘플      ', 70002, 0, CAST(0x9C50045A AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (243, N'휘플휘플      ', 50012, 0, CAST(0x9C50045A AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (244, N'기하        ', 40001, 1, CAST(0x9C50045B AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (245, N'기하        ', 60001, 1, CAST(0x9C50045B AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (246, N'기하        ', 50002, 1, CAST(0x9C50045B AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (247, N'뽀오        ', 70001, 0, CAST(0x9C50045C AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (248, N'뽀오        ', 50001, 0, CAST(0x9C50045C AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (249, N'팡케루       ', 70002, 0, CAST(0x9C50045D AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (250, N'팡케루       ', 50001, 0, CAST(0x9C50045D AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (251, N'휘플휘플      ', 60001, 1, CAST(0x9C50045E AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (252, N'휘플휘플      ', 40001, 1, CAST(0x9C50046D AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (253, N'xkall     ', 70002, 0, CAST(0x9C50049C AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (254, N'xkall     ', 50012, 0, CAST(0x9C50049C AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (255, N'푸르푸르      ', 70001, 0, CAST(0x9C5004AA AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (256, N'푸르푸르      ', 50001, 0, CAST(0x9C5004AA AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (257, N'666       ', 70001, 0, CAST(0x9C50052E AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (258, N'666       ', 50012, 0, CAST(0x9C50052E AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (259, N'666       ', 40001, 1, CAST(0x9C500530 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (260, N'666       ', 60001, 1, CAST(0x9C500530 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (261, N'dma..     ', 70001, 0, CAST(0x9C51054F AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (262, N'dma..     ', 50012, 0, CAST(0x9C51054F AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (263, N'dma..     ', 40002, 1, CAST(0x9C510551 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (264, N'dma..     ', 60005, 1, CAST(0x9C510551 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (265, N'dma..     ', 50001, 1, CAST(0x9C510552 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (266, N'ds        ', 70002, 0, CAST(0x9C520329 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (267, N'ds        ', 50001, 0, CAST(0x9C520329 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (268, N'ds        ', 40002, 1, CAST(0x9C52032B AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (269, N'ds        ', 60002, 1, CAST(0x9C52032C AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (270, N'와일드플래닛    ', 70002, 0, CAST(0x9C55026D AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (271, N'와일드플래닛    ', 50001, 0, CAST(0x9C55026D AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (272, N'테스트용      ', 70002, 0, CAST(0x9C5502FB AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (273, N'테스트용      ', 50002, 0, CAST(0x9C5502FB AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (274, N'asd       ', 70002, 0, CAST(0x9C550381 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (275, N'asd       ', 50012, 0, CAST(0x9C550381 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (276, N'Luna      ', 60004, 1, CAST(0x9C550382 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (277, N'sam       ', 70002, 0, CAST(0x9C5504DD AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (278, N'sam       ', 50012, 0, CAST(0x9C5504DD AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (279, N'ss        ', 70002, 0, CAST(0x9C5604A2 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (280, N'ss        ', 50003, 0, CAST(0x9C5604A2 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (281, N'루나        ', 70002, 0, CAST(0x9C5E0371 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (282, N'루나        ', 50004, 0, CAST(0x9C5E0371 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (283, N'한승연       ', 70002, 0, CAST(0x9C6102B3 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (284, N'한승연       ', 50012, 0, CAST(0x9C6102B3 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (285, N'한승연       ', 40001, 1, CAST(0x9C6102B4 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (286, N'한승연       ', 60001, 1, CAST(0x9C6102B4 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (287, N'얄리몬       ', 70002, 0, CAST(0x9C610320 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (288, N'얄리몬       ', 50004, 0, CAST(0x9C610320 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (289, N'1         ', 70002, 0, CAST(0x9C650062 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (290, N'1         ', 50011, 0, CAST(0x9C650062 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (291, N'ppp       ', 70002, 0, CAST(0x9C6B02F2 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (292, N'ppp       ', 50012, 0, CAST(0x9C6B02F2 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (293, N'ppp       ', 70001, 1, CAST(0x9C6B02F6 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (294, N'pppp      ', 70002, 0, CAST(0x9C6C0245 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (295, N'pppp      ', 50011, 0, CAST(0x9C6C0245 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (296, N'exxa      ', 60002, 1, CAST(0x9C6C0248 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (297, N'exxa      ', 50012, 1, CAST(0x9C6C0248 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (298, N'ppppp     ', 70002, 0, CAST(0x9C6D03C9 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (299, N'ppppp     ', 50011, 0, CAST(0x9C6D03C9 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (300, N'exxa      ', 50001, 1, CAST(0x9C6D03CC AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (301, N'exxa      ', 60004, 1, CAST(0x9C6D03CC AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (302, N'미순        ', 70001, 0, CAST(0x9C6E0408 AS SmallDateTime))
GO
print 'Processed 300 total records'
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (303, N'미순        ', 50011, 0, CAST(0x9C6E0408 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (304, N'별이        ', 50004, 1, CAST(0x9C6E040C AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (305, N'별이        ', 60004, 1, CAST(0x9C6E0418 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (306, N'KGDA      ', 70001, 0, CAST(0x9C73023F AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (307, N'KGDA      ', 50003, 0, CAST(0x9C73023F AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (308, N'KGDA      ', 60006, 1, CAST(0x9C730248 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (309, N'KGDA      ', 50004, 1, CAST(0x9C730249 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (310, N'KGDA      ', 50011, 1, CAST(0x9C73024A AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (311, N'클스        ', 70002, 0, CAST(0x9C7C042C AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (312, N'클스        ', 50003, 0, CAST(0x9C7C042C AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (313, N'asdd      ', 70002, 0, CAST(0x9CA202DD AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (314, N'asdd      ', 50012, 0, CAST(0x9CA202DD AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (315, N'ddwee     ', 70001, 0, CAST(0x9CA202E1 AS SmallDateTime))
INSERT [dbo].[TRADE_AVATAR] ([tradeNum], [characterName], [itemCode], [dealMode], [buyTime]) VALUES (316, N'ddwee     ', 50003, 0, CAST(0x9CA202E1 AS SmallDateTime))
SET IDENTITY_INSERT [dbo].[TRADE_AVATAR] OFF
/****** Object:  View [dbo].[RANKING]    Script Date: 10/29/2018 19:50:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE VIEW [dbo].[RANKING]
AS
	SELECT characterName, exper
	FROM CHARACTER_BASE
GO
/****** Object:  Table [dbo].[INVEN_TYPE]    Script Date: 10/29/2018 19:50:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[INVEN_TYPE](
	[invenNum] [int] IDENTITY(1,1) NOT NULL,
	[characterName] [nchar](10) NOT NULL,
	[itemCode] [int] NOT NULL,
	[itemUse] [bit] NOT NULL,
 CONSTRAINT [PK__INVEN_TYPE] PRIMARY KEY CLUSTERED 
(
	[invenNum] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
SET IDENTITY_INSERT [dbo].[INVEN_TYPE] ON
INSERT [dbo].[INVEN_TYPE] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (1, N'시발        ', 70001, 1)
INSERT [dbo].[INVEN_TYPE] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (2, N'exxa      ', 70001, 0)
INSERT [dbo].[INVEN_TYPE] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (3, N'마성의유희열    ', 70001, 1)
INSERT [dbo].[INVEN_TYPE] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (4, N'엄앵란       ', 70002, 1)
INSERT [dbo].[INVEN_TYPE] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (5, N'test1     ', 70001, 1)
INSERT [dbo].[INVEN_TYPE] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (6, N'test2     ', 70002, 0)
INSERT [dbo].[INVEN_TYPE] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (11, N'곰발바닥      ', 70002, 1)
INSERT [dbo].[INVEN_TYPE] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (12, N'엄앵란       ', 70001, 0)
INSERT [dbo].[INVEN_TYPE] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (13, N'test1     ', 70002, 0)
INSERT [dbo].[INVEN_TYPE] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (14, N'exxa      ', 70002, 1)
INSERT [dbo].[INVEN_TYPE] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (15, N'zzz       ', 70001, 1)
INSERT [dbo].[INVEN_TYPE] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (16, N'select    ', 70001, 1)
INSERT [dbo].[INVEN_TYPE] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (17, N'test2     ', 70001, 1)
INSERT [dbo].[INVEN_TYPE] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (18, N'수령님       ', 70001, 1)
INSERT [dbo].[INVEN_TYPE] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (19, N'망크        ', 70002, 1)
INSERT [dbo].[INVEN_TYPE] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (20, N'유희열       ', 70001, 1)
INSERT [dbo].[INVEN_TYPE] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (21, N'신성일       ', 70001, 1)
INSERT [dbo].[INVEN_TYPE] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (22, N'위대한 수령님   ', 70001, 1)
INSERT [dbo].[INVEN_TYPE] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (23, N'신성일투      ', 70002, 0)
INSERT [dbo].[INVEN_TYPE] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (24, N'유희열       ', 70002, 0)
INSERT [dbo].[INVEN_TYPE] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (25, N'성기사뿌뿌뿡    ', 70002, 1)
INSERT [dbo].[INVEN_TYPE] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (26, N'터프가이      ', 70001, 0)
INSERT [dbo].[INVEN_TYPE] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (27, N'터프가이      ', 70002, 1)
INSERT [dbo].[INVEN_TYPE] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (28, N'엔진        ', 70002, 1)
INSERT [dbo].[INVEN_TYPE] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (29, N'Luna      ', 70001, 1)
INSERT [dbo].[INVEN_TYPE] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (30, N'신성일투      ', 70001, 1)
INSERT [dbo].[INVEN_TYPE] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (31, N'qwer      ', 70001, 1)
INSERT [dbo].[INVEN_TYPE] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (32, N'별이        ', 70001, 1)
INSERT [dbo].[INVEN_TYPE] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (33, N'Luna      ', 70002, 0)
INSERT [dbo].[INVEN_TYPE] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (34, N'제라드       ', 70001, 1)
INSERT [dbo].[INVEN_TYPE] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (35, N'판타지 스타    ', 70001, 1)
INSERT [dbo].[INVEN_TYPE] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (36, N'젠장        ', 70002, 1)
INSERT [dbo].[INVEN_TYPE] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (37, N'아쭈구리      ', 70001, 1)
INSERT [dbo].[INVEN_TYPE] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (38, N'타우렌함유     ', 70002, 1)
INSERT [dbo].[INVEN_TYPE] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (39, N'기획서용      ', 70001, 1)
INSERT [dbo].[INVEN_TYPE] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (40, N'님이그걸왜먹어여  ', 70002, 1)
INSERT [dbo].[INVEN_TYPE] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (41, N'aka       ', 70002, 1)
INSERT [dbo].[INVEN_TYPE] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (42, N'777       ', 70002, 1)
INSERT [dbo].[INVEN_TYPE] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (43, N'test3     ', 70002, 1)
INSERT [dbo].[INVEN_TYPE] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (44, N'test      ', 70002, 1)
INSERT [dbo].[INVEN_TYPE] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (45, N'나밥줘       ', 70001, 1)
INSERT [dbo].[INVEN_TYPE] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (46, N'어익쿠       ', 70002, 1)
INSERT [dbo].[INVEN_TYPE] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (47, N'장난감       ', 70001, 1)
INSERT [dbo].[INVEN_TYPE] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (48, N'dddd      ', 70002, 1)
INSERT [dbo].[INVEN_TYPE] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (49, N'mOok      ', 70002, 1)
INSERT [dbo].[INVEN_TYPE] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (50, N'오쿠샤       ', 70001, 1)
INSERT [dbo].[INVEN_TYPE] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (51, N'DREAMEXE  ', 70001, 1)
INSERT [dbo].[INVEN_TYPE] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (52, N'다덤벼       ', 70002, 1)
INSERT [dbo].[INVEN_TYPE] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (53, N'깜빡했다      ', 70002, 1)
INSERT [dbo].[INVEN_TYPE] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (54, N'야메        ', 70001, 1)
INSERT [dbo].[INVEN_TYPE] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (55, N'밥은먹고다니니   ', 70002, 1)
INSERT [dbo].[INVEN_TYPE] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (56, N'blackhole ', 70001, 1)
INSERT [dbo].[INVEN_TYPE] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (57, N'공구함       ', 70001, 1)
INSERT [dbo].[INVEN_TYPE] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (58, N'째뮌        ', 70001, 1)
INSERT [dbo].[INVEN_TYPE] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (59, N'aaa       ', 70001, 1)
INSERT [dbo].[INVEN_TYPE] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (60, N'가오리       ', 70001, 1)
INSERT [dbo].[INVEN_TYPE] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (61, N'후훗        ', 70002, 1)
INSERT [dbo].[INVEN_TYPE] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (62, N'도라에몽      ', 70002, 1)
INSERT [dbo].[INVEN_TYPE] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (63, N'ff        ', 70001, 1)
INSERT [dbo].[INVEN_TYPE] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (64, N'asdf      ', 70001, 1)
INSERT [dbo].[INVEN_TYPE] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (65, N'fdsfdsf   ', 70002, 1)
INSERT [dbo].[INVEN_TYPE] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (66, N'5555      ', 70002, 1)
INSERT [dbo].[INVEN_TYPE] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (67, N'dsscsd    ', 70002, 1)
INSERT [dbo].[INVEN_TYPE] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (68, N'뿌잉        ', 70002, 1)
INSERT [dbo].[INVEN_TYPE] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (69, N'기하        ', 70001, 1)
INSERT [dbo].[INVEN_TYPE] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (70, N'aaaaaf    ', 70001, 1)
INSERT [dbo].[INVEN_TYPE] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (71, N'휘플휘플      ', 70002, 1)
INSERT [dbo].[INVEN_TYPE] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (72, N'뽀오        ', 70001, 1)
INSERT [dbo].[INVEN_TYPE] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (73, N'팡케루       ', 70002, 1)
INSERT [dbo].[INVEN_TYPE] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (74, N'xkall     ', 70002, 1)
INSERT [dbo].[INVEN_TYPE] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (75, N'푸르푸르      ', 70001, 1)
INSERT [dbo].[INVEN_TYPE] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (76, N'666       ', 70001, 1)
INSERT [dbo].[INVEN_TYPE] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (77, N'dma..     ', 70001, 1)
INSERT [dbo].[INVEN_TYPE] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (78, N'ds        ', 70002, 1)
INSERT [dbo].[INVEN_TYPE] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (79, N'와일드플래닛    ', 70002, 1)
INSERT [dbo].[INVEN_TYPE] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (80, N'테스트용      ', 70002, 1)
INSERT [dbo].[INVEN_TYPE] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (81, N'asd       ', 70002, 1)
INSERT [dbo].[INVEN_TYPE] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (82, N'sam       ', 70002, 1)
INSERT [dbo].[INVEN_TYPE] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (83, N'ss        ', 70002, 1)
INSERT [dbo].[INVEN_TYPE] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (84, N'루나        ', 70002, 1)
INSERT [dbo].[INVEN_TYPE] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (85, N'한승연       ', 70002, 1)
INSERT [dbo].[INVEN_TYPE] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (86, N'얄리몬       ', 70002, 1)
INSERT [dbo].[INVEN_TYPE] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (87, N'1         ', 70002, 1)
INSERT [dbo].[INVEN_TYPE] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (88, N'ppp       ', 70002, 1)
INSERT [dbo].[INVEN_TYPE] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (89, N'ppp       ', 70001, 0)
INSERT [dbo].[INVEN_TYPE] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (90, N'pppp      ', 70002, 1)
INSERT [dbo].[INVEN_TYPE] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (91, N'ppppp     ', 70002, 1)
INSERT [dbo].[INVEN_TYPE] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (92, N'미순        ', 70001, 1)
INSERT [dbo].[INVEN_TYPE] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (93, N'KGDA      ', 70001, 1)
INSERT [dbo].[INVEN_TYPE] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (94, N'클스        ', 70002, 1)
INSERT [dbo].[INVEN_TYPE] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (95, N'asdd      ', 70002, 1)
INSERT [dbo].[INVEN_TYPE] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (96, N'ddwee     ', 70001, 1)
SET IDENTITY_INSERT [dbo].[INVEN_TYPE] OFF
/****** Object:  Table [dbo].[INVEN_THEME]    Script Date: 10/29/2018 19:50:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[INVEN_THEME](
	[invenNum] [int] IDENTITY(1,1) NOT NULL,
	[characterName] [nchar](10) NOT NULL,
	[itemCode] [int] NOT NULL,
	[itemUse] [bit] NOT NULL,
 CONSTRAINT [PK__INVEN_THEME] PRIMARY KEY CLUSTERED 
(
	[invenNum] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
SET IDENTITY_INSERT [dbo].[INVEN_THEME] ON
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (1, N'시발        ', 32003, 1)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (2, N'exxa      ', 31001, 0)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (3, N'마성의유희열    ', 38001, 0)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (4, N'엄앵란       ', 32001, 0)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (5, N'test1     ', 32001, 1)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (6, N'test2     ', 31002, 1)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (7, N'곰발바닥      ', 32003, 1)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (8, N'엄앵란       ', 31002, 0)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (9, N'엄앵란       ', 32002, 0)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (11, N'엄앵란       ', 37002, 0)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (12, N'엄앵란       ', 38001, 0)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (13, N'엄앵란       ', 36001, 0)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (14, N'엄앵란       ', 31001, 1)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (15, N'망크        ', 31001, 1)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (16, N'마성의유희열    ', 37001, 1)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (17, N'수령님       ', 37001, 1)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (18, N'유희열       ', 37001, 1)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (19, N'위대한 수령님   ', 31001, 1)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (20, N'엄앵란       ', 32003, 0)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (21, N'엄앵란       ', 33001, 0)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (22, N'신성일투      ', 31001, 1)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (23, N'성기사뿌뿌뿡    ', 32001, 1)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (24, N'터프가이      ', 32001, 0)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (25, N'엔진        ', 32003, 1)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (26, N'터프가이      ', 31001, 0)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (27, N'터프가이      ', 31002, 0)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (28, N'터프가이      ', 32002, 0)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (29, N'터프가이      ', 32003, 0)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (30, N'터프가이      ', 33001, 0)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (31, N'터프가이      ', 33002, 1)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (32, N'터프가이      ', 33003, 0)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (33, N'터프가이      ', 34001, 0)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (34, N'터프가이      ', 35001, 0)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (35, N'터프가이      ', 35002, 0)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (36, N'터프가이      ', 36001, 0)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (37, N'터프가이      ', 37001, 0)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (38, N'터프가이      ', 37002, 0)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (39, N'터프가이      ', 38001, 0)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (40, N'신성일       ', 37001, 1)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (41, N'엄앵란       ', 33002, 0)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (42, N'엄앵란       ', 33003, 0)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (43, N'엄앵란       ', 34001, 0)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (44, N'엄앵란       ', 35001, 0)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (45, N'엄앵란       ', 35002, 0)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (46, N'엄앵란       ', 37001, 0)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (47, N'test2     ', 37001, 0)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (48, N'별이        ', 31002, 0)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (49, N'qwer      ', 36001, 1)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (50, N'Luna      ', 37002, 0)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (51, N'Luna      ', 33002, 1)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (52, N'Luna      ', 35002, 0)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (53, N'Luna      ', 36001, 0)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (54, N'제라드       ', 32001, 1)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (55, N'아쭈구리      ', 31001, 1)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (56, N'타우렌함유     ', 32003, 1)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (57, N'기획서용      ', 37002, 1)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (58, N'님이그걸왜먹어여  ', 33001, 1)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (59, N'Luna      ', 32002, 0)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (60, N'aka       ', 32001, 1)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (61, N'777       ', 36001, 1)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (62, N'test3     ', 31001, 1)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (63, N'test      ', 37002, 1)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (64, N'나밥줘       ', 37002, 1)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (65, N'어익쿠       ', 31001, 1)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (66, N'장난감       ', 32003, 1)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (67, N'mOok      ', 32003, 1)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (68, N'오쿠샤       ', 36001, 1)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (69, N'DREAMEXE  ', 32003, 1)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (70, N'다덤벼       ', 32003, 1)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (71, N'깜빡했다      ', 32002, 1)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (72, N'야메        ', 31002, 1)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (73, N'밥은먹고다니니   ', 37002, 1)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (74, N'blackhole ', 37002, 1)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (75, N'공구함       ', 32003, 1)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (76, N'째뮌        ', 31001, 1)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (77, N'aaa       ', 32001, 1)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (78, N'가오리       ', 33001, 1)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (79, N'후훗        ', 31001, 0)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (80, N'후훗        ', 31002, 1)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (81, N'후훗        ', 33001, 0)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (82, N'도라에몽      ', 32003, 1)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (83, N'ff        ', 32003, 1)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (84, N'asdf      ', 32001, 1)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (85, N'fdsfdsf   ', 31002, 1)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (86, N'5555      ', 33001, 1)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (87, N'dsscsd    ', 37001, 1)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (88, N'뿌잉        ', 32003, 1)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (89, N'기하        ', 31001, 1)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (90, N'aaaaaf    ', 31001, 1)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (91, N'휘플휘플      ', 38002, 1)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (92, N'뽀오        ', 32003, 1)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (93, N'팡케루       ', 37002, 1)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (94, N'xkall     ', 37001, 1)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (95, N'푸르푸르      ', 31002, 1)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (96, N'666       ', 33003, 1)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (97, N'dma..     ', 38002, 1)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (98, N'dma..     ', 32002, 0)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (99, N'ds        ', 32003, 1)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (100, N'와일드플래닛    ', 37002, 1)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (101, N'별이        ', 32001, 0)
GO
print 'Processed 100 total records'
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (102, N'테스트용      ', 32003, 1)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (103, N'asd       ', 32002, 1)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (104, N'Luna      ', 35001, 0)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (105, N'sam       ', 31001, 1)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (106, N'ss        ', 32003, 1)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (107, N'루나        ', 32001, 1)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (108, N'한승연       ', 37002, 1)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (109, N'한승연       ', 31001, 0)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (110, N'얄리몬       ', 32001, 1)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (111, N'1         ', 32003, 1)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (112, N'ppp       ', 37001, 0)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (113, N'ppp       ', 33001, 0)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (114, N'ppp       ', 33002, 1)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (115, N'exxa      ', 32002, 0)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (116, N'pppp      ', 32002, 1)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (117, N'exxa      ', 33003, 0)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (118, N'ppppp     ', 34001, 1)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (119, N'exxa      ', 32001, 1)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (120, N'미순        ', 33001, 1)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (121, N'별이        ', 33001, 1)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (122, N'KGDA      ', 31001, 1)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (123, N'클스        ', 37002, 1)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (124, N'asdd      ', 31001, 1)
INSERT [dbo].[INVEN_THEME] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (125, N'ddwee     ', 31001, 1)
SET IDENTITY_INSERT [dbo].[INVEN_THEME] OFF
/****** Object:  Table [dbo].[INVEN_OBJECT]    Script Date: 10/29/2018 19:50:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[INVEN_OBJECT](
	[invenNum] [int] IDENTITY(1,1) NOT NULL,
	[characterName] [nchar](10) NOT NULL,
	[itemCode] [int] NOT NULL,
	[itemUse] [bit] NOT NULL,
 CONSTRAINT [PK__INVEN_OBJECT] PRIMARY KEY CLUSTERED 
(
	[invenNum] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
SET IDENTITY_INSERT [dbo].[INVEN_OBJECT] ON
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (1, N'시발        ', 17011, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (2, N'exxa      ', 17011, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (4, N'엄앵란       ', 17011, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (5, N'test1     ', 17011, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (6, N'test2     ', 17011, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (7, N'곰발바닥      ', 17011, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (20, N'망크        ', 17011, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (26, N'수령님       ', 17011, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (34, N'엄앵란       ', 12031, 0)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (36, N'엄앵란       ', 12031, 0)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (37, N'엄앵란       ', 12031, 0)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (38, N'엄앵란       ', 12031, 0)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (41, N'엄앵란       ', 13021, 0)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (43, N'엄앵란       ', 13021, 0)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (47, N'엄앵란       ', 14051, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (48, N'엄앵란       ', 14071, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (50, N'엄앵란       ', 16011, 0)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (54, N'엄앵란       ', 16022, 0)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (57, N'엄앵란       ', 16023, 0)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (58, N'엄앵란       ', 16023, 0)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (63, N'마성의유희열    ', 11011, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (64, N'마성의유희열    ', 11021, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (65, N'유희열       ', 17011, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (66, N'위대한 수령님   ', 17011, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (68, N'엄앵란       ', 11022, 0)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (70, N'엄앵란       ', 11022, 0)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (71, N'엄앵란       ', 11022, 0)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (73, N'엄앵란       ', 11042, 0)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (74, N'엄앵란       ', 11042, 0)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (75, N'엄앵란       ', 12011, 0)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (76, N'엄앵란       ', 12011, 0)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (78, N'엄앵란       ', 13021, 0)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (79, N'신성일투      ', 17011, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (80, N'test1     ', 11022, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (82, N'유희열       ', 16012, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (84, N'유희열       ', 16012, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (86, N'유희열       ', 16012, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (87, N'유희열       ', 16012, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (88, N'유희열       ', 16012, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (89, N'유희열       ', 16012, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (90, N'유희열       ', 16012, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (92, N'유희열       ', 16012, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (93, N'유희열       ', 16012, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (94, N'유희열       ', 16012, 0)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (95, N'유희열       ', 16012, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (97, N'유희열       ', 16012, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (98, N'test1     ', 11041, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (99, N'test1     ', 12013, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (100, N'성기사뿌뿌뿡    ', 17011, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (101, N'터프가이      ', 17011, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (102, N'엔진        ', 17011, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (109, N'터프가이      ', 12011, 0)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (119, N'엔진        ', 16011, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (120, N'엔진        ', 11011, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (121, N'엔진        ', 17011, 0)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (122, N'엔진        ', 11031, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (123, N'엔진        ', 12013, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (124, N'유희열       ', 16011, 0)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (125, N'신성일       ', 17011, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (127, N'test2     ', 11022, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (128, N'test2     ', 11041, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (129, N'별이        ', 17011, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (130, N'qwer      ', 17011, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (131, N'Luna      ', 17011, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (139, N'신성일투      ', 12031, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (140, N'Luna      ', 17011, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (141, N'Luna      ', 17011, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (142, N'제라드       ', 17011, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (143, N'별이        ', 12031, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (145, N'별이        ', 14071, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (146, N'별이        ', 14051, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (147, N'아쭈구리      ', 17011, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (149, N'Luna      ', 17011, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (152, N'타우렌함유     ', 17011, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (153, N'유희열       ', 17011, 0)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (154, N'망크        ', 17011, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (155, N'망크        ', 17011, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (156, N'망크        ', 17011, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (157, N'망크        ', 12032, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (158, N'망크        ', 16012, 0)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (159, N'망크        ', 16012, 0)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (160, N'기획서용      ', 17011, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (161, N'엄앵란       ', 14071, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (162, N'엄앵란       ', 14071, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (163, N'엄앵란       ', 14071, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (164, N'엄앵란       ', 14071, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (165, N'엄앵란       ', 14071, 0)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (166, N'엄앵란       ', 14071, 0)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (167, N'엄앵란       ', 14071, 0)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (168, N'엄앵란       ', 14071, 0)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (169, N'엄앵란       ', 14071, 0)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (170, N'엄앵란       ', 14071, 0)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (171, N'엄앵란       ', 14071, 0)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (172, N'엄앵란       ', 14071, 0)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (173, N'엄앵란       ', 14071, 0)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (174, N'엄앵란       ', 14071, 0)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (175, N'엄앵란       ', 14071, 0)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (176, N'엄앵란       ', 14071, 0)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (177, N'엄앵란       ', 14071, 0)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (178, N'엄앵란       ', 14071, 0)
GO
print 'Processed 100 total records'
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (179, N'엄앵란       ', 14071, 0)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (180, N'엄앵란       ', 14071, 0)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (181, N'엄앵란       ', 14071, 0)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (182, N'엄앵란       ', 14071, 0)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (183, N'엄앵란       ', 14071, 0)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (184, N'엄앵란       ', 14051, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (185, N'엄앵란       ', 14051, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (186, N'엄앵란       ', 14051, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (187, N'엄앵란       ', 14051, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (188, N'엄앵란       ', 14051, 0)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (189, N'엄앵란       ', 14051, 0)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (190, N'엄앵란       ', 14051, 0)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (191, N'엄앵란       ', 14051, 0)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (192, N'엄앵란       ', 14051, 0)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (193, N'엄앵란       ', 14051, 0)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (194, N'님이그걸왜먹어여  ', 17011, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (198, N'터프가이      ', 14051, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (199, N'터프가이      ', 14071, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (201, N'터프가이      ', 14051, 0)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (202, N'aka       ', 17011, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (203, N'777       ', 17011, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (204, N'터프가이      ', 11011, 0)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (209, N'터프가이      ', 12013, 0)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (213, N'터프가이      ', 16011, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (214, N'터프가이      ', 16012, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (215, N'터프가이      ', 16011, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (218, N'터프가이      ', 11042, 0)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (219, N'터프가이      ', 11041, 0)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (220, N'test3     ', 17011, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (221, N'터프가이      ', 11031, 0)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (222, N'터프가이      ', 12031, 0)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (223, N'터프가이      ', 16012, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (224, N'터프가이      ', 16011, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (225, N'터프가이      ', 16011, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (226, N'test      ', 17011, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (227, N'나밥줘       ', 17011, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (228, N'어익쿠       ', 17011, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (229, N'장난감       ', 17011, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (230, N'mOok      ', 17011, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (231, N'오쿠샤       ', 17011, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (232, N'DREAMEXE  ', 17011, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (233, N'다덤벼       ', 17011, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (234, N'깜빡했다      ', 17011, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (235, N'야메        ', 17011, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (236, N'밥은먹고다니니   ', 17011, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (237, N'blackhole ', 17011, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (238, N'공구함       ', 17011, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (239, N'째뮌        ', 17011, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (240, N'aaa       ', 17011, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (241, N'가오리       ', 17011, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (242, N'다덤벼       ', 12011, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (243, N'후훗        ', 17011, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (244, N'후훗        ', 11021, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (245, N'후훗        ', 11022, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (246, N'도라에몽      ', 17011, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (247, N'ff        ', 17011, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (248, N'asdf      ', 17011, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (249, N'fdsfdsf   ', 17011, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (250, N'5555      ', 17011, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (251, N'dsscsd    ', 17011, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (252, N'뿌잉        ', 17011, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (253, N'기하        ', 17011, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (254, N'aaaaaf    ', 17011, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (255, N'휘플휘플      ', 17011, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (256, N'뽀오        ', 17011, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (257, N'팡케루       ', 17011, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (258, N'휘플휘플      ', 12031, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (259, N'휘플휘플      ', 11011, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (260, N'xkall     ', 17011, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (261, N'푸르푸르      ', 17011, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (262, N'별이        ', 11042, 0)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (263, N'별이        ', 11041, 0)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (264, N'별이        ', 12032, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (265, N'별이        ', 11031, 0)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (266, N'666       ', 17011, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (267, N'dma..     ', 17011, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (268, N'dma..     ', 11031, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (269, N'ds        ', 17011, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (270, N'ds        ', 11022, 0)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (271, N'와일드플래닛    ', 17011, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (272, N'와일드플래닛    ', 11031, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (273, N'와일드플래닛    ', 12033, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (274, N'와일드플래닛    ', 16012, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (276, N'별이        ', 11041, 0)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (277, N'Luna      ', 11011, 0)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (279, N'Luna      ', 11031, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (280, N'Luna      ', 11031, 0)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (281, N'Luna      ', 11031, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (282, N'Luna      ', 12021, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (283, N'Luna      ', 12033, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (286, N'Luna      ', 12033, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (287, N'Luna      ', 12033, 0)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (288, N'Luna      ', 16012, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (289, N'Luna      ', 16012, 0)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (290, N'Luna      ', 14071, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (291, N'Luna      ', 14051, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (292, N'Luna      ', 16012, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (293, N'Luna      ', 16023, 0)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (294, N'Luna      ', 16023, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (297, N'Luna      ', 16012, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (298, N'Luna      ', 16012, 0)
GO
print 'Processed 200 total records'
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (299, N'Luna      ', 16012, 0)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (300, N'Luna      ', 16012, 0)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (301, N'Luna      ', 12022, 0)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (302, N'Luna      ', 12022, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (303, N'Luna      ', 12023, 0)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (304, N'Luna      ', 12023, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (305, N'테스트용      ', 17011, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (306, N'asd       ', 17011, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (307, N'Luna      ', 11031, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (308, N'Luna      ', 11022, 0)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (309, N'sam       ', 17011, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (310, N'ss        ', 17011, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (311, N'루나        ', 17011, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (312, N'한승연       ', 17011, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (313, N'한승연       ', 11011, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (314, N'얄리몬       ', 17011, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (315, N'터프가이      ', 12022, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (316, N'터프가이      ', 12022, 0)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (317, N'터프가이      ', 12033, 0)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (318, N'1         ', 17011, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (319, N'ppp       ', 17011, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (320, N'ppp       ', 11042, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (321, N'exxa      ', 16011, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (323, N'exxa      ', 16011, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (324, N'exxa      ', 11011, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (327, N'pppp      ', 17011, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (328, N'exxa      ', 11042, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (330, N'ppppp     ', 17011, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (331, N'exxa      ', 14071, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (332, N'exxa      ', 14051, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (333, N'미순        ', 17011, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (334, N'별이        ', 12031, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (336, N'KGDA      ', 17011, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (337, N'KGDA      ', 11022, 0)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (338, N'클스        ', 17011, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (339, N'asdd      ', 17011, 1)
INSERT [dbo].[INVEN_OBJECT] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (340, N'ddwee     ', 17011, 1)
SET IDENTITY_INSERT [dbo].[INVEN_OBJECT] OFF
/****** Object:  Table [dbo].[INVEN_HEAD]    Script Date: 10/29/2018 19:50:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[INVEN_HEAD](
	[invenNum] [int] IDENTITY(1,1) NOT NULL,
	[characterName] [nchar](10) NOT NULL,
	[itemCode] [int] NOT NULL,
	[itemUse] [bit] NOT NULL,
 CONSTRAINT [PK__INVEN_HEAD] PRIMARY KEY CLUSTERED 
(
	[invenNum] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
SET IDENTITY_INSERT [dbo].[INVEN_HEAD] ON
INSERT [dbo].[INVEN_HEAD] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (1, N'엄앵란       ', 40001, 0)
INSERT [dbo].[INVEN_HEAD] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (2, N'엄앵란       ', 40002, 1)
INSERT [dbo].[INVEN_HEAD] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (8, N'test1     ', 40002, 1)
INSERT [dbo].[INVEN_HEAD] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (9, N'exxa      ', 40002, 1)
INSERT [dbo].[INVEN_HEAD] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (10, N'test2     ', 40001, 0)
INSERT [dbo].[INVEN_HEAD] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (11, N'유희열       ', 40001, 1)
INSERT [dbo].[INVEN_HEAD] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (12, N'유희열       ', 40002, 0)
INSERT [dbo].[INVEN_HEAD] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (13, N'test2     ', 40002, 1)
INSERT [dbo].[INVEN_HEAD] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (14, N'터프가이      ', 40002, 1)
INSERT [dbo].[INVEN_HEAD] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (15, N'터프가이      ', 40001, 0)
INSERT [dbo].[INVEN_HEAD] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (16, N'엔진        ', 40002, 1)
INSERT [dbo].[INVEN_HEAD] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (17, N'test1     ', 40001, 0)
INSERT [dbo].[INVEN_HEAD] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (18, N'Luna      ', 40001, 0)
INSERT [dbo].[INVEN_HEAD] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (19, N'Luna      ', 40002, 1)
INSERT [dbo].[INVEN_HEAD] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (20, N'신성일투      ', 40002, 1)
INSERT [dbo].[INVEN_HEAD] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (21, N'신성일투      ', 40001, 0)
INSERT [dbo].[INVEN_HEAD] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (22, N'별이        ', 40002, 1)
INSERT [dbo].[INVEN_HEAD] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (23, N'나밥줘       ', 40001, 1)
INSERT [dbo].[INVEN_HEAD] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (24, N'mOok      ', 40002, 0)
INSERT [dbo].[INVEN_HEAD] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (25, N'공구함       ', 40001, 1)
INSERT [dbo].[INVEN_HEAD] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (26, N'다덤벼       ', 40001, 0)
INSERT [dbo].[INVEN_HEAD] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (27, N'후훗        ', 40001, 1)
INSERT [dbo].[INVEN_HEAD] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (28, N'기하        ', 40001, 1)
INSERT [dbo].[INVEN_HEAD] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (29, N'휘플휘플      ', 40001, 0)
INSERT [dbo].[INVEN_HEAD] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (30, N'666       ', 40001, 0)
INSERT [dbo].[INVEN_HEAD] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (31, N'dma..     ', 40002, 1)
INSERT [dbo].[INVEN_HEAD] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (32, N'ds        ', 40002, 0)
INSERT [dbo].[INVEN_HEAD] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (33, N'한승연       ', 40001, 1)
SET IDENTITY_INSERT [dbo].[INVEN_HEAD] OFF
/****** Object:  Table [dbo].[INVEN_COLOR]    Script Date: 10/29/2018 19:50:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[INVEN_COLOR](
	[invenNum] [int] IDENTITY(1,1) NOT NULL,
	[characterName] [nchar](10) NOT NULL,
	[itemCode] [int] NOT NULL,
	[itemUse] [bit] NOT NULL,
 CONSTRAINT [PK__INVEN_COLOR] PRIMARY KEY CLUSTERED 
(
	[invenNum] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
SET IDENTITY_INSERT [dbo].[INVEN_COLOR] ON
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (1, N'시발        ', 50011, 0)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (2, N'exxa      ', 50011, 1)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (3, N'마성의유희열    ', 50011, 1)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (4, N'엄앵란       ', 50011, 0)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (5, N'test1     ', 50012, 0)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (6, N'test2     ', 50012, 0)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (11, N'곰발바닥      ', 50011, 1)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (12, N'엄앵란       ', 50001, 0)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (13, N'엄앵란       ', 50002, 0)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (14, N'엄앵란       ', 50003, 0)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (15, N'엄앵란       ', 50012, 0)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (16, N'test1     ', 50004, 0)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (17, N'test1     ', 50002, 1)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (18, N'test1     ', 50001, 0)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (19, N'exxa      ', 50002, 0)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (20, N'zzz       ', 50012, 1)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (21, N'select    ', 50003, 1)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (22, N'수령님       ', 50004, 1)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (23, N'망크        ', 50001, 1)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (24, N'엄앵란       ', 50004, 1)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (25, N'유희열       ', 50001, 0)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (26, N'신성일       ', 50002, 1)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (27, N'위대한 수령님   ', 50011, 1)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (28, N'신성일투      ', 50003, 1)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (29, N'유희열       ', 50011, 0)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (30, N'유희열       ', 50012, 1)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (31, N'유희열       ', 50002, 0)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (32, N'유희열       ', 50003, 0)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (33, N'유희열       ', 50004, 0)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (34, N'test2     ', 50001, 0)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (35, N'test2     ', 50011, 0)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (36, N'성기사뿌뿌뿡    ', 50001, 1)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (37, N'터프가이      ', 50012, 0)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (38, N'엔진        ', 50004, 0)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (39, N'터프가이      ', 50011, 0)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (40, N'터프가이      ', 50001, 1)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (41, N'터프가이      ', 50002, 0)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (42, N'터프가이      ', 50003, 0)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (43, N'Luna      ', 50002, 0)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (44, N'엔진        ', 50011, 1)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (45, N'터프가이      ', 50004, 0)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (46, N'test2     ', 50004, 0)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (47, N'test2     ', 50002, 1)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (48, N'신성일투      ', 50012, 0)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (49, N'신성일투      ', 50002, 0)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (50, N'qwer      ', 50012, 1)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (51, N'별이        ', 50011, 0)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (52, N'Luna      ', 50003, 0)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (53, N'Luna      ', 50004, 0)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (54, N'Luna      ', 50011, 1)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (55, N'Luna      ', 50001, 0)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (56, N'제라드       ', 50002, 1)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (57, N'판타지 스타    ', 50002, 1)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (58, N'젠장        ', 50001, 1)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (59, N'아쭈구리      ', 50002, 1)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (60, N'신성일투      ', 50011, 0)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (61, N'신성일투      ', 50004, 0)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (62, N'신성일투      ', 50001, 0)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (63, N'타우렌함유     ', 50001, 1)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (64, N'기획서용      ', 50002, 1)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (65, N'님이그걸왜먹어여  ', 50003, 1)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (66, N'aka       ', 50002, 1)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (67, N'777       ', 50003, 1)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (68, N'test3     ', 50002, 1)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (69, N'test      ', 50002, 1)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (70, N'나밥줘       ', 50004, 1)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (71, N'어익쿠       ', 50002, 1)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (72, N'장난감       ', 50004, 1)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (73, N'dddd      ', 50002, 1)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (74, N'mOok      ', 50012, 1)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (75, N'오쿠샤       ', 50011, 1)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (76, N'DREAMEXE  ', 50003, 1)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (77, N'다덤벼       ', 50002, 0)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (78, N'깜빡했다      ', 50011, 1)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (79, N'야메        ', 50004, 1)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (80, N'밥은먹고다니니   ', 50011, 1)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (81, N'blackhole ', 50012, 1)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (82, N'공구함       ', 50011, 1)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (83, N'째뮌        ', 50003, 1)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (84, N'aaa       ', 50001, 1)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (85, N'가오리       ', 50011, 1)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (86, N'다덤벼       ', 50012, 1)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (87, N'후훗        ', 50011, 0)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (88, N'후훗        ', 50012, 1)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (89, N'도라에몽      ', 50001, 1)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (90, N'ff        ', 50004, 1)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (91, N'asdf      ', 50002, 1)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (92, N'fdsfdsf   ', 50001, 1)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (93, N'5555      ', 50001, 1)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (94, N'dsscsd    ', 50002, 1)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (95, N'뿌잉        ', 50004, 1)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (96, N'기하        ', 50012, 0)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (97, N'aaaaaf    ', 50003, 1)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (98, N'휘플휘플      ', 50012, 1)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (99, N'기하        ', 50002, 1)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (100, N'뽀오        ', 50001, 1)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (101, N'팡케루       ', 50001, 1)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (102, N'xkall     ', 50012, 1)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (103, N'푸르푸르      ', 50001, 1)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (104, N'666       ', 50012, 1)
GO
print 'Processed 100 total records'
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (105, N'dma..     ', 50012, 1)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (106, N'dma..     ', 50001, 0)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (107, N'ds        ', 50001, 1)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (108, N'와일드플래닛    ', 50001, 1)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (109, N'테스트용      ', 50002, 1)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (110, N'asd       ', 50012, 1)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (111, N'sam       ', 50012, 1)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (112, N'ss        ', 50003, 1)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (113, N'루나        ', 50004, 1)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (114, N'한승연       ', 50012, 1)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (115, N'얄리몬       ', 50004, 1)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (116, N'1         ', 50011, 1)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (117, N'ppp       ', 50012, 1)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (118, N'pppp      ', 50011, 1)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (119, N'exxa      ', 50012, 0)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (120, N'ppppp     ', 50011, 1)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (121, N'exxa      ', 50001, 0)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (122, N'미순        ', 50011, 1)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (123, N'별이        ', 50004, 1)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (124, N'KGDA      ', 50003, 0)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (125, N'KGDA      ', 50004, 0)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (126, N'KGDA      ', 50011, 1)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (127, N'클스        ', 50003, 1)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (128, N'asdd      ', 50012, 1)
INSERT [dbo].[INVEN_COLOR] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (129, N'ddwee     ', 50003, 1)
SET IDENTITY_INSERT [dbo].[INVEN_COLOR] OFF
/****** Object:  Table [dbo].[INVEN_BODY]    Script Date: 10/29/2018 19:50:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[INVEN_BODY](
	[invenNum] [int] IDENTITY(1,1) NOT NULL,
	[characterName] [nchar](10) NOT NULL,
	[itemCode] [int] NOT NULL,
	[itemUse] [bit] NOT NULL,
 CONSTRAINT [PK__INVEN_BODY] PRIMARY KEY CLUSTERED 
(
	[invenNum] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
SET IDENTITY_INSERT [dbo].[INVEN_BODY] ON
INSERT [dbo].[INVEN_BODY] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (1, N'엄앵란       ', 60003, 0)
INSERT [dbo].[INVEN_BODY] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (2, N'엄앵란       ', 60005, 0)
INSERT [dbo].[INVEN_BODY] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (3, N'엄앵란       ', 60001, 0)
INSERT [dbo].[INVEN_BODY] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (4, N'엄앵란       ', 60002, 0)
INSERT [dbo].[INVEN_BODY] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (5, N'엄앵란       ', 60006, 0)
INSERT [dbo].[INVEN_BODY] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (6, N'엄앵란       ', 60008, 1)
INSERT [dbo].[INVEN_BODY] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (7, N'엄앵란       ', 60004, 0)
INSERT [dbo].[INVEN_BODY] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (8, N'엄앵란       ', 60007, 0)
INSERT [dbo].[INVEN_BODY] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (9, N'test1     ', 60002, 0)
INSERT [dbo].[INVEN_BODY] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (10, N'test1     ', 60003, 0)
INSERT [dbo].[INVEN_BODY] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (11, N'test1     ', 60001, 0)
INSERT [dbo].[INVEN_BODY] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (12, N'test2     ', 60001, 0)
INSERT [dbo].[INVEN_BODY] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (13, N'유희열       ', 60001, 0)
INSERT [dbo].[INVEN_BODY] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (14, N'유희열       ', 60002, 0)
INSERT [dbo].[INVEN_BODY] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (15, N'유희열       ', 60003, 0)
INSERT [dbo].[INVEN_BODY] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (16, N'유희열       ', 60004, 1)
INSERT [dbo].[INVEN_BODY] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (17, N'유희열       ', 60005, 0)
INSERT [dbo].[INVEN_BODY] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (18, N'유희열       ', 60006, 0)
INSERT [dbo].[INVEN_BODY] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (19, N'유희열       ', 60007, 0)
INSERT [dbo].[INVEN_BODY] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (20, N'유희열       ', 60008, 0)
INSERT [dbo].[INVEN_BODY] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (21, N'test2     ', 60002, 0)
INSERT [dbo].[INVEN_BODY] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (22, N'test2     ', 60006, 0)
INSERT [dbo].[INVEN_BODY] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (23, N'터프가이      ', 60002, 0)
INSERT [dbo].[INVEN_BODY] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (24, N'터프가이      ', 60003, 0)
INSERT [dbo].[INVEN_BODY] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (25, N'터프가이      ', 60004, 1)
INSERT [dbo].[INVEN_BODY] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (26, N'터프가이      ', 60005, 0)
INSERT [dbo].[INVEN_BODY] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (27, N'터프가이      ', 60006, 0)
INSERT [dbo].[INVEN_BODY] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (28, N'터프가이      ', 60007, 0)
INSERT [dbo].[INVEN_BODY] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (29, N'터프가이      ', 60008, 0)
INSERT [dbo].[INVEN_BODY] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (30, N'터프가이      ', 60001, 0)
INSERT [dbo].[INVEN_BODY] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (31, N'엔진        ', 60007, 1)
INSERT [dbo].[INVEN_BODY] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (32, N'test1     ', 60006, 0)
INSERT [dbo].[INVEN_BODY] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (33, N'test2     ', 60004, 1)
INSERT [dbo].[INVEN_BODY] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (34, N'test2     ', 60007, 0)
INSERT [dbo].[INVEN_BODY] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (35, N'test2     ', 60008, 0)
INSERT [dbo].[INVEN_BODY] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (36, N'신성일투      ', 60002, 1)
INSERT [dbo].[INVEN_BODY] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (37, N'신성일투      ', 60005, 0)
INSERT [dbo].[INVEN_BODY] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (38, N'test1     ', 60004, 1)
INSERT [dbo].[INVEN_BODY] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (39, N'Luna      ', 60005, 0)
INSERT [dbo].[INVEN_BODY] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (40, N'Luna      ', 60006, 1)
INSERT [dbo].[INVEN_BODY] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (41, N'Luna      ', 60007, 0)
INSERT [dbo].[INVEN_BODY] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (42, N'Luna      ', 60008, 0)
INSERT [dbo].[INVEN_BODY] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (43, N'Luna      ', 60001, 0)
INSERT [dbo].[INVEN_BODY] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (44, N'신성일투      ', 60001, 0)
INSERT [dbo].[INVEN_BODY] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (45, N'신성일투      ', 60003, 0)
INSERT [dbo].[INVEN_BODY] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (46, N'신성일투      ', 60004, 0)
INSERT [dbo].[INVEN_BODY] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (47, N'신성일투      ', 60006, 0)
INSERT [dbo].[INVEN_BODY] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (48, N'신성일투      ', 60007, 0)
INSERT [dbo].[INVEN_BODY] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (49, N'신성일투      ', 60008, 0)
INSERT [dbo].[INVEN_BODY] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (50, N'Luna      ', 60003, 0)
INSERT [dbo].[INVEN_BODY] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (51, N'나밥줘       ', 60001, 1)
INSERT [dbo].[INVEN_BODY] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (52, N'어익쿠       ', 60001, 1)
INSERT [dbo].[INVEN_BODY] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (53, N'mOok      ', 60006, 0)
INSERT [dbo].[INVEN_BODY] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (54, N'다덤벼       ', 60001, 1)
INSERT [dbo].[INVEN_BODY] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (55, N'후훗        ', 60001, 1)
INSERT [dbo].[INVEN_BODY] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (56, N'기하        ', 60001, 1)
INSERT [dbo].[INVEN_BODY] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (57, N'휘플휘플      ', 60001, 1)
INSERT [dbo].[INVEN_BODY] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (58, N'666       ', 60001, 0)
INSERT [dbo].[INVEN_BODY] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (59, N'dma..     ', 60005, 1)
INSERT [dbo].[INVEN_BODY] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (60, N'ds        ', 60002, 0)
INSERT [dbo].[INVEN_BODY] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (61, N'Luna      ', 60004, 0)
INSERT [dbo].[INVEN_BODY] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (62, N'한승연       ', 60001, 1)
INSERT [dbo].[INVEN_BODY] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (63, N'exxa      ', 60002, 0)
INSERT [dbo].[INVEN_BODY] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (64, N'exxa      ', 60004, 1)
INSERT [dbo].[INVEN_BODY] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (65, N'별이        ', 60004, 1)
INSERT [dbo].[INVEN_BODY] ([invenNum], [characterName], [itemCode], [itemUse]) VALUES (66, N'KGDA      ', 60006, 1)
SET IDENTITY_INSERT [dbo].[INVEN_BODY] OFF
/****** Object:  Table [dbo].[FRIEND_LIST]    Script Date: 10/29/2018 19:50:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[FRIEND_LIST](
	[characterName] [nchar](10) NOT NULL,
	[fName] [nchar](10) NOT NULL
) ON [PRIMARY]
GO
INSERT [dbo].[FRIEND_LIST] ([characterName], [fName]) VALUES (N'엄앵란       ', N'곰발바닥      ')
INSERT [dbo].[FRIEND_LIST] ([characterName], [fName]) VALUES (N'엄앵란       ', N'마성의유희열    ')
INSERT [dbo].[FRIEND_LIST] ([characterName], [fName]) VALUES (N'엄앵란       ', N'수령님       ')
INSERT [dbo].[FRIEND_LIST] ([characterName], [fName]) VALUES (N'수령님       ', N'엄앵란       ')
INSERT [dbo].[FRIEND_LIST] ([characterName], [fName]) VALUES (N'수령님       ', N'마성의유희열    ')
INSERT [dbo].[FRIEND_LIST] ([characterName], [fName]) VALUES (N'test1     ', N'test2     ')
INSERT [dbo].[FRIEND_LIST] ([characterName], [fName]) VALUES (N'test1     ', N'엄앵란       ')
INSERT [dbo].[FRIEND_LIST] ([characterName], [fName]) VALUES (N'Luna      ', N'엄앵란       ')
INSERT [dbo].[FRIEND_LIST] ([characterName], [fName]) VALUES (N'Luna      ', N'마성의유희열    ')
INSERT [dbo].[FRIEND_LIST] ([characterName], [fName]) VALUES (N'Luna      ', N'수령님       ')
INSERT [dbo].[FRIEND_LIST] ([characterName], [fName]) VALUES (N'Luna      ', N'유희열       ')
INSERT [dbo].[FRIEND_LIST] ([characterName], [fName]) VALUES (N'Luna      ', N'신성일       ')
/****** Object:  Table [dbo].[CHARACTER_CUSTOM]    Script Date: 10/29/2018 19:50:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[CHARACTER_CUSTOM](
	[characterName] [nchar](10) NOT NULL,
	[characterType] [int] NOT NULL,
	[characterColor] [int] NOT NULL,
	[characterHead] [int] NULL,
	[characterBody] [int] NULL
) ON [PRIMARY]
GO
INSERT [dbo].[CHARACTER_CUSTOM] ([characterName], [characterType], [characterColor], [characterHead], [characterBody]) VALUES (N'시발        ', 5, 17, NULL, NULL)
INSERT [dbo].[CHARACTER_CUSTOM] ([characterName], [characterType], [characterColor], [characterHead], [characterBody]) VALUES (N'exxa      ', 14, 2, 9, 64)
INSERT [dbo].[CHARACTER_CUSTOM] ([characterName], [characterType], [characterColor], [characterHead], [characterBody]) VALUES (N'마성의유희열    ', 3, 3, NULL, NULL)
INSERT [dbo].[CHARACTER_CUSTOM] ([characterName], [characterType], [characterColor], [characterHead], [characterBody]) VALUES (N'엄앵란       ', 4, 24, 2, 6)
INSERT [dbo].[CHARACTER_CUSTOM] ([characterName], [characterType], [characterColor], [characterHead], [characterBody]) VALUES (N'test1     ', 5, 17, 8, 38)
INSERT [dbo].[CHARACTER_CUSTOM] ([characterName], [characterType], [characterColor], [characterHead], [characterBody]) VALUES (N'test2     ', 17, 47, 13, 33)
INSERT [dbo].[CHARACTER_CUSTOM] ([characterName], [characterType], [characterColor], [characterHead], [characterBody]) VALUES (N'곰발바닥      ', 11, 11, NULL, NULL)
INSERT [dbo].[CHARACTER_CUSTOM] ([characterName], [characterType], [characterColor], [characterHead], [characterBody]) VALUES (N'zzz       ', 15, 20, NULL, NULL)
INSERT [dbo].[CHARACTER_CUSTOM] ([characterName], [characterType], [characterColor], [characterHead], [characterBody]) VALUES (N'select    ', 16, 21, NULL, NULL)
INSERT [dbo].[CHARACTER_CUSTOM] ([characterName], [characterType], [characterColor], [characterHead], [characterBody]) VALUES (N'수령님       ', 18, 22, NULL, NULL)
INSERT [dbo].[CHARACTER_CUSTOM] ([characterName], [characterType], [characterColor], [characterHead], [characterBody]) VALUES (N'망크        ', 19, 23, NULL, NULL)
INSERT [dbo].[CHARACTER_CUSTOM] ([characterName], [characterType], [characterColor], [characterHead], [characterBody]) VALUES (N'유희열       ', 20, 30, 11, 16)
INSERT [dbo].[CHARACTER_CUSTOM] ([characterName], [characterType], [characterColor], [characterHead], [characterBody]) VALUES (N'신성일       ', 21, 26, NULL, NULL)
INSERT [dbo].[CHARACTER_CUSTOM] ([characterName], [characterType], [characterColor], [characterHead], [characterBody]) VALUES (N'위대한 수령님   ', 22, 27, NULL, NULL)
INSERT [dbo].[CHARACTER_CUSTOM] ([characterName], [characterType], [characterColor], [characterHead], [characterBody]) VALUES (N'신성일투      ', 30, 28, 20, 36)
INSERT [dbo].[CHARACTER_CUSTOM] ([characterName], [characterType], [characterColor], [characterHead], [characterBody]) VALUES (N'성기사뿌뿌뿡    ', 25, 36, NULL, NULL)
INSERT [dbo].[CHARACTER_CUSTOM] ([characterName], [characterType], [characterColor], [characterHead], [characterBody]) VALUES (N'터프가이      ', 27, 40, 14, 25)
INSERT [dbo].[CHARACTER_CUSTOM] ([characterName], [characterType], [characterColor], [characterHead], [characterBody]) VALUES (N'엔진        ', 28, 44, 16, 31)
INSERT [dbo].[CHARACTER_CUSTOM] ([characterName], [characterType], [characterColor], [characterHead], [characterBody]) VALUES (N'제라드       ', 34, 56, NULL, NULL)
INSERT [dbo].[CHARACTER_CUSTOM] ([characterName], [characterType], [characterColor], [characterHead], [characterBody]) VALUES (N'판타지 스타    ', 35, 57, NULL, NULL)
INSERT [dbo].[CHARACTER_CUSTOM] ([characterName], [characterType], [characterColor], [characterHead], [characterBody]) VALUES (N'젠장        ', 36, 58, NULL, NULL)
INSERT [dbo].[CHARACTER_CUSTOM] ([characterName], [characterType], [characterColor], [characterHead], [characterBody]) VALUES (N'아쭈구리      ', 37, 59, NULL, NULL)
INSERT [dbo].[CHARACTER_CUSTOM] ([characterName], [characterType], [characterColor], [characterHead], [characterBody]) VALUES (N'타우렌함유     ', 38, 63, NULL, NULL)
INSERT [dbo].[CHARACTER_CUSTOM] ([characterName], [characterType], [characterColor], [characterHead], [characterBody]) VALUES (N'기획서용      ', 39, 64, NULL, NULL)
INSERT [dbo].[CHARACTER_CUSTOM] ([characterName], [characterType], [characterColor], [characterHead], [characterBody]) VALUES (N'님이그걸왜먹어여  ', 40, 65, NULL, NULL)
INSERT [dbo].[CHARACTER_CUSTOM] ([characterName], [characterType], [characterColor], [characterHead], [characterBody]) VALUES (N'aka       ', 41, 66, NULL, NULL)
INSERT [dbo].[CHARACTER_CUSTOM] ([characterName], [characterType], [characterColor], [characterHead], [characterBody]) VALUES (N'777       ', 42, 67, NULL, NULL)
INSERT [dbo].[CHARACTER_CUSTOM] ([characterName], [characterType], [characterColor], [characterHead], [characterBody]) VALUES (N'test3     ', 43, 68, NULL, NULL)
INSERT [dbo].[CHARACTER_CUSTOM] ([characterName], [characterType], [characterColor], [characterHead], [characterBody]) VALUES (N'test      ', 44, 69, NULL, NULL)
INSERT [dbo].[CHARACTER_CUSTOM] ([characterName], [characterType], [characterColor], [characterHead], [characterBody]) VALUES (N'나밥줘       ', 45, 70, 23, 51)
INSERT [dbo].[CHARACTER_CUSTOM] ([characterName], [characterType], [characterColor], [characterHead], [characterBody]) VALUES (N'어익쿠       ', 46, 71, NULL, 52)
INSERT [dbo].[CHARACTER_CUSTOM] ([characterName], [characterType], [characterColor], [characterHead], [characterBody]) VALUES (N'장난감       ', 47, 72, NULL, NULL)
INSERT [dbo].[CHARACTER_CUSTOM] ([characterName], [characterType], [characterColor], [characterHead], [characterBody]) VALUES (N'dddd      ', 48, 73, NULL, NULL)
INSERT [dbo].[CHARACTER_CUSTOM] ([characterName], [characterType], [characterColor], [characterHead], [characterBody]) VALUES (N'mOok      ', 49, 74, NULL, NULL)
INSERT [dbo].[CHARACTER_CUSTOM] ([characterName], [characterType], [characterColor], [characterHead], [characterBody]) VALUES (N'오쿠샤       ', 50, 75, NULL, NULL)
INSERT [dbo].[CHARACTER_CUSTOM] ([characterName], [characterType], [characterColor], [characterHead], [characterBody]) VALUES (N'DREAMEXE  ', 51, 76, NULL, NULL)
INSERT [dbo].[CHARACTER_CUSTOM] ([characterName], [characterType], [characterColor], [characterHead], [characterBody]) VALUES (N'다덤벼       ', 52, 86, NULL, 54)
INSERT [dbo].[CHARACTER_CUSTOM] ([characterName], [characterType], [characterColor], [characterHead], [characterBody]) VALUES (N'깜빡했다      ', 53, 78, NULL, NULL)
INSERT [dbo].[CHARACTER_CUSTOM] ([characterName], [characterType], [characterColor], [characterHead], [characterBody]) VALUES (N'야메        ', 54, 79, NULL, NULL)
INSERT [dbo].[CHARACTER_CUSTOM] ([characterName], [characterType], [characterColor], [characterHead], [characterBody]) VALUES (N'밥은먹고다니니   ', 55, 80, NULL, NULL)
INSERT [dbo].[CHARACTER_CUSTOM] ([characterName], [characterType], [characterColor], [characterHead], [characterBody]) VALUES (N'blackhole ', 56, 81, NULL, NULL)
INSERT [dbo].[CHARACTER_CUSTOM] ([characterName], [characterType], [characterColor], [characterHead], [characterBody]) VALUES (N'공구함       ', 57, 82, 25, NULL)
INSERT [dbo].[CHARACTER_CUSTOM] ([characterName], [characterType], [characterColor], [characterHead], [characterBody]) VALUES (N'째뮌        ', 58, 83, NULL, NULL)
INSERT [dbo].[CHARACTER_CUSTOM] ([characterName], [characterType], [characterColor], [characterHead], [characterBody]) VALUES (N'aaa       ', 59, 84, NULL, NULL)
INSERT [dbo].[CHARACTER_CUSTOM] ([characterName], [characterType], [characterColor], [characterHead], [characterBody]) VALUES (N'가오리       ', 60, 85, NULL, NULL)
INSERT [dbo].[CHARACTER_CUSTOM] ([characterName], [characterType], [characterColor], [characterHead], [characterBody]) VALUES (N'후훗        ', 61, 88, 27, 55)
INSERT [dbo].[CHARACTER_CUSTOM] ([characterName], [characterType], [characterColor], [characterHead], [characterBody]) VALUES (N'도라에몽      ', 62, 89, NULL, NULL)
INSERT [dbo].[CHARACTER_CUSTOM] ([characterName], [characterType], [characterColor], [characterHead], [characterBody]) VALUES (N'ff        ', 63, 90, NULL, NULL)
INSERT [dbo].[CHARACTER_CUSTOM] ([characterName], [characterType], [characterColor], [characterHead], [characterBody]) VALUES (N'asdf      ', 64, 91, NULL, NULL)
INSERT [dbo].[CHARACTER_CUSTOM] ([characterName], [characterType], [characterColor], [characterHead], [characterBody]) VALUES (N'fdsfdsf   ', 65, 92, NULL, NULL)
INSERT [dbo].[CHARACTER_CUSTOM] ([characterName], [characterType], [characterColor], [characterHead], [characterBody]) VALUES (N'5555      ', 66, 93, NULL, NULL)
INSERT [dbo].[CHARACTER_CUSTOM] ([characterName], [characterType], [characterColor], [characterHead], [characterBody]) VALUES (N'dsscsd    ', 67, 94, NULL, NULL)
INSERT [dbo].[CHARACTER_CUSTOM] ([characterName], [characterType], [characterColor], [characterHead], [characterBody]) VALUES (N'뿌잉        ', 68, 95, NULL, NULL)
INSERT [dbo].[CHARACTER_CUSTOM] ([characterName], [characterType], [characterColor], [characterHead], [characterBody]) VALUES (N'기하        ', 69, 99, 28, 56)
INSERT [dbo].[CHARACTER_CUSTOM] ([characterName], [characterType], [characterColor], [characterHead], [characterBody]) VALUES (N'aaaaaf    ', 70, 97, NULL, NULL)
INSERT [dbo].[CHARACTER_CUSTOM] ([characterName], [characterType], [characterColor], [characterHead], [characterBody]) VALUES (N'휘플휘플      ', 71, 98, NULL, 57)
INSERT [dbo].[CHARACTER_CUSTOM] ([characterName], [characterType], [characterColor], [characterHead], [characterBody]) VALUES (N'뽀오        ', 72, 100, NULL, NULL)
INSERT [dbo].[CHARACTER_CUSTOM] ([characterName], [characterType], [characterColor], [characterHead], [characterBody]) VALUES (N'팡케루       ', 73, 101, NULL, NULL)
INSERT [dbo].[CHARACTER_CUSTOM] ([characterName], [characterType], [characterColor], [characterHead], [characterBody]) VALUES (N'xkall     ', 74, 102, NULL, NULL)
INSERT [dbo].[CHARACTER_CUSTOM] ([characterName], [characterType], [characterColor], [characterHead], [characterBody]) VALUES (N'푸르푸르      ', 75, 103, NULL, NULL)
INSERT [dbo].[CHARACTER_CUSTOM] ([characterName], [characterType], [characterColor], [characterHead], [characterBody]) VALUES (N'666       ', 76, 104, NULL, NULL)
INSERT [dbo].[CHARACTER_CUSTOM] ([characterName], [characterType], [characterColor], [characterHead], [characterBody]) VALUES (N'dma..     ', 77, 105, 31, 59)
INSERT [dbo].[CHARACTER_CUSTOM] ([characterName], [characterType], [characterColor], [characterHead], [characterBody]) VALUES (N'ds        ', 78, 107, NULL, NULL)
INSERT [dbo].[CHARACTER_CUSTOM] ([characterName], [characterType], [characterColor], [characterHead], [characterBody]) VALUES (N'와일드플래닛    ', 79, 108, NULL, NULL)
INSERT [dbo].[CHARACTER_CUSTOM] ([characterName], [characterType], [characterColor], [characterHead], [characterBody]) VALUES (N'테스트용      ', 80, 109, NULL, NULL)
INSERT [dbo].[CHARACTER_CUSTOM] ([characterName], [characterType], [characterColor], [characterHead], [characterBody]) VALUES (N'asd       ', 81, 110, NULL, NULL)
INSERT [dbo].[CHARACTER_CUSTOM] ([characterName], [characterType], [characterColor], [characterHead], [characterBody]) VALUES (N'sam       ', 82, 111, NULL, NULL)
INSERT [dbo].[CHARACTER_CUSTOM] ([characterName], [characterType], [characterColor], [characterHead], [characterBody]) VALUES (N'ss        ', 83, 112, NULL, NULL)
INSERT [dbo].[CHARACTER_CUSTOM] ([characterName], [characterType], [characterColor], [characterHead], [characterBody]) VALUES (N'루나        ', 84, 113, NULL, NULL)
INSERT [dbo].[CHARACTER_CUSTOM] ([characterName], [characterType], [characterColor], [characterHead], [characterBody]) VALUES (N'한승연       ', 85, 114, 33, 62)
INSERT [dbo].[CHARACTER_CUSTOM] ([characterName], [characterType], [characterColor], [characterHead], [characterBody]) VALUES (N'얄리몬       ', 86, 115, NULL, NULL)
INSERT [dbo].[CHARACTER_CUSTOM] ([characterName], [characterType], [characterColor], [characterHead], [characterBody]) VALUES (N'1         ', 87, 116, NULL, NULL)
INSERT [dbo].[CHARACTER_CUSTOM] ([characterName], [characterType], [characterColor], [characterHead], [characterBody]) VALUES (N'ppp       ', 88, 117, NULL, NULL)
INSERT [dbo].[CHARACTER_CUSTOM] ([characterName], [characterType], [characterColor], [characterHead], [characterBody]) VALUES (N'pppp      ', 90, 118, NULL, NULL)
INSERT [dbo].[CHARACTER_CUSTOM] ([characterName], [characterType], [characterColor], [characterHead], [characterBody]) VALUES (N'ppppp     ', 91, 120, NULL, NULL)
INSERT [dbo].[CHARACTER_CUSTOM] ([characterName], [characterType], [characterColor], [characterHead], [characterBody]) VALUES (N'미순        ', 92, 122, NULL, NULL)
INSERT [dbo].[CHARACTER_CUSTOM] ([characterName], [characterType], [characterColor], [characterHead], [characterBody]) VALUES (N'KGDA      ', 93, 126, NULL, 66)
INSERT [dbo].[CHARACTER_CUSTOM] ([characterName], [characterType], [characterColor], [characterHead], [characterBody]) VALUES (N'클스        ', 94, 127, NULL, NULL)
INSERT [dbo].[CHARACTER_CUSTOM] ([characterName], [characterType], [characterColor], [characterHead], [characterBody]) VALUES (N'asdd      ', 95, 128, NULL, NULL)
INSERT [dbo].[CHARACTER_CUSTOM] ([characterName], [characterType], [characterColor], [characterHead], [characterBody]) VALUES (N'ddwee     ', 96, 129, NULL, NULL)
INSERT [dbo].[CHARACTER_CUSTOM] ([characterName], [characterType], [characterColor], [characterHead], [characterBody]) VALUES (N'Luna      ', 29, 54, 19, 40)
INSERT [dbo].[CHARACTER_CUSTOM] ([characterName], [characterType], [characterColor], [characterHead], [characterBody]) VALUES (N'qwer      ', 31, 50, NULL, NULL)
INSERT [dbo].[CHARACTER_CUSTOM] ([characterName], [characterType], [characterColor], [characterHead], [characterBody]) VALUES (N'별이        ', 32, 123, 22, 65)
/****** Object:  Table [dbo].[PLANET_OBJECT]    Script Date: 10/29/2018 19:50:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[PLANET_OBJECT](
	[planetName] [nchar](10) NOT NULL,
	[objectNum] [int] NOT NULL,
	[tileNum] [smallint] NOT NULL
) ON [PRIMARY]
GO
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'발         ', 1, 46)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'exxa      ', 2, 46)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'아이유       ', 65, 46)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'쉬르벨       ', 4, 46)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'test1     ', 5, 46)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'test2     ', 6, 46)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'쿡         ', 7, 46)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'testtest  ', 26, 46)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'쉐끼루       ', 79, 46)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'쉬르벨       ', 162, 109)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'test1     ', 80, 39)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'피콜로제국     ', 314, 46)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'소녀시대      ', 63, 30)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'소녀시대      ', 64, 71)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'파란집       ', 66, 46)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'개터프       ', 315, 69)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'아이유       ', 82, 56)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'아이유       ', 84, 153)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'1         ', 318, 46)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'아이유       ', 86, 162)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'아이유       ', 87, 81)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'아이유       ', 88, 87)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'아이유       ', 89, 60)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'아이유       ', 90, 209)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'ppp       ', 319, 46)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'아이유       ', 92, 424)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'아이유       ', 93, 184)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'아이유       ', 95, 175)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'ppp       ', 320, 43)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'아이유       ', 97, 114)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'test1     ', 98, 58)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'test1     ', 99, 57)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'뿡뿡이네      ', 100, 46)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'개터프       ', 101, 46)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'쉬르벨       ', 163, 135)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'행성이다      ', 131, 46)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'쉬르벨       ', 47, 38)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'쉬르벨       ', 48, 19)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'쉬르벨       ', 161, 33)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'쉬르벨       ', 164, 339)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'쉬르벨       ', 184, 188)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'앵란이는 어디에  ', 125, 46)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'행성이다      ', 304, 165)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'행성이다      ', 283, 31)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'행성이다      ', 281, 63)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'행성이다      ', 279, 407)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'행성이다      ', 286, 42)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'쉐끼루       ', 139, 28)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'행성이다      ', 288, 80)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'제라드       ', 142, 46)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'개터프       ', 199, 157)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'쉬르벨       ', 185, 97)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'개터프       ', 223, 342)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'별이        ', 145, 92)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'별이        ', 143, 26)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'별이        ', 146, 188)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'개터프       ', 224, 345)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'행성이다      ', 141, 708)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'행성이다      ', 140, 1328)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'행성이다      ', 294, 52)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'행성이다      ', 149, 577)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'행성이다      ', 291, 202)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'타우농장      ', 152, 46)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'망크별       ', 154, 587)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'망크별       ', 155, 1662)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'망크별       ', 156, 1779)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'개터프       ', 225, 278)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'망크별       ', 157, 1040)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'기획서용행성    ', 160, 46)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'쉬르벨       ', 186, 112)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'쉬르벨       ', 187, 336)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'주인님차단하세요  ', 194, 46)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'행성이다      ', 290, 151)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'루나의 행성    ', 311, 46)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'개터프       ', 198, 207)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'test3     ', 220, 46)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'bone      ', 202, 46)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'aaa       ', 203, 46)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'개터프       ', 213, 148)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'개터프       ', 214, 102)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'개터프       ', 215, 65)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'exxa      ', 321, 108)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'냐하항       ', 226, 46)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'황소별       ', 227, 46)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'어이쿠야      ', 228, 46)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'나메크성      ', 229, 46)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'puchon    ', 230, 46)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'그냥별       ', 231, 46)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'QWDQW     ', 232, 46)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'포더호드      ', 233, 46)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'구구1       ', 234, 46)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'혹성2b      ', 235, 46)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'밥먹자       ', 236, 46)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'안드로메다     ', 237, 46)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'공구박스      ', 238, 46)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'쨈성        ', 239, 46)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'aa        ', 240, 46)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'달         ', 241, 46)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'포더호드      ', 242, 110)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'지구~       ', 243, 46)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'지구~       ', 245, 72)
GO
print 'Processed 100 total records'
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'지구~       ', 244, 41)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'네르크란스     ', 246, 46)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'qqq       ', 247, 46)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'446       ', 248, 46)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'gfgfg     ', 249, 46)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'6666      ', 250, 46)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'zxczx     ', 251, 46)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'뽀잉        ', 252, 46)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'쥬신의별      ', 253, 46)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'ddf       ', 254, 46)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'스튜디오뮤트    ', 255, 46)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'옴니        ', 256, 46)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'팡팡게루      ', 257, 46)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'스튜디오뮤트    ', 259, 67)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'스튜디오뮤트    ', 258, 135)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'moya      ', 260, 46)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'Goat      ', 261, 46)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'별이        ', 264, 27)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'444       ', 266, 46)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'123       ', 267, 46)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'123       ', 268, 20)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'fef       ', 269, 46)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'안녕하세요     ', 271, 46)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'안녕하세요     ', 272, 133)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'안녕하세요     ', 273, 13)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'안녕하세요     ', 274, 26)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'행성이다      ', 292, 346)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'행성이다      ', 282, 87)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'행성이다      ', 302, 610)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'카라        ', 312, 46)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'행성이다      ', 297, 507)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'내꺼        ', 305, 46)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'qweqwe    ', 306, 46)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'행성이다      ', 307, 224)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'SAM       ', 309, 46)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'ss        ', 310, 46)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'카라        ', 313, 352)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'exxa      ', 324, 92)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'exxa      ', 323, 36)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'내 행성      ', 330, 46)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'미순        ', 333, 46)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'pppp의 행성  ', 327, 46)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'exxa      ', 328, 267)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'별이        ', 334, 112)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'exxa      ', 332, 157)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'exxa      ', 331, 214)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'MEMORY    ', 336, 46)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'virtual   ', 338, 46)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'adad      ', 339, 46)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'dwd       ', 340, 46)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'망크별       ', 20, 46)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'이런        ', 147, 46)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'프레임워크     ', 102, 46)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'프레임워크     ', 120, 57)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'프레임워크     ', 122, 156)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'프레임워크     ', 123, 61)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'프레임워크     ', 119, 208)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'test2     ', 128, 177)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'test2     ', 127, 53)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'별이        ', 129, 46)
INSERT [dbo].[PLANET_OBJECT] ([planetName], [objectNum], [tileNum]) VALUES (N'염소        ', 130, 46)
/****** Object:  Table [dbo].[PLANET_CUSTOM]    Script Date: 10/29/2018 19:50:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[PLANET_CUSTOM](
	[planetName] [nchar](10) NOT NULL,
	[planetTheme] [int] NOT NULL,
	[planetTerrain] [int] NOT NULL,
	[planetMemo] [nchar](50) NULL
) ON [PRIMARY]
GO
INSERT [dbo].[PLANET_CUSTOM] ([planetName], [planetTheme], [planetTerrain], [planetMemo]) VALUES (N'발         ', 1, 80001, N'시발의 발 행성 임!                                       ')
INSERT [dbo].[PLANET_CUSTOM] ([planetName], [planetTheme], [planetTerrain], [planetMemo]) VALUES (N'exxa      ', 119, 80001, N'내꺼임                                               ')
INSERT [dbo].[PLANET_CUSTOM] ([planetName], [planetTheme], [planetTerrain], [planetMemo]) VALUES (N'소녀시대      ', 16, 80001, N'마성의유희열의 소녀시대 행성 임!                                ')
INSERT [dbo].[PLANET_CUSTOM] ([planetName], [planetTheme], [planetTerrain], [planetMemo]) VALUES (N'쉬르벨       ', 14, 80001, N'엄앵란의 저녁식사                                         ')
INSERT [dbo].[PLANET_CUSTOM] ([planetName], [planetTheme], [planetTerrain], [planetMemo]) VALUES (N'test1     ', 5, 80001, N'사놨더니 왜 이모냥이야                                      ')
INSERT [dbo].[PLANET_CUSTOM] ([planetName], [planetTheme], [planetTerrain], [planetMemo]) VALUES (N'test2     ', 6, 80001, N'뉴비에요 늅늅늅 봐주셈요 늅늅늅                                 ')
INSERT [dbo].[PLANET_CUSTOM] ([planetName], [planetTheme], [planetTerrain], [planetMemo]) VALUES (N'쿡         ', 7, 80001, N'곰발바닥의 쿡 행성 임!                                     ')
INSERT [dbo].[PLANET_CUSTOM] ([planetName], [planetTheme], [planetTerrain], [planetMemo]) VALUES (N'망크별       ', 15, 80001, N'망크의 망크별 행성 임!                                     ')
INSERT [dbo].[PLANET_CUSTOM] ([planetName], [planetTheme], [planetTerrain], [planetMemo]) VALUES (N'testtest  ', 17, 80001, N'수령님의 testtest 행성 임!                               ')
INSERT [dbo].[PLANET_CUSTOM] ([planetName], [planetTheme], [planetTerrain], [planetMemo]) VALUES (N'아이유       ', 18, 80001, N'아이유를 노리는 매의 행성                                    ')
INSERT [dbo].[PLANET_CUSTOM] ([planetName], [planetTheme], [planetTerrain], [planetMemo]) VALUES (N'파란집       ', 19, 80012, N'위대한 수령님의 파란집 행성 임!                                ')
INSERT [dbo].[PLANET_CUSTOM] ([planetName], [planetTheme], [planetTerrain], [planetMemo]) VALUES (N'쉐끼루       ', 22, 80001, N'신성일투의 쉐끼루 행성 임!                                   ')
INSERT [dbo].[PLANET_CUSTOM] ([planetName], [planetTheme], [planetTerrain], [planetMemo]) VALUES (N'뿡뿡이네      ', 23, 80008, N'성기사뿌뿌뿡의 뿡뿡이네 행성 임!                                ')
INSERT [dbo].[PLANET_CUSTOM] ([planetName], [planetTheme], [planetTerrain], [planetMemo]) VALUES (N'개터프       ', 31, 80004, N'안녕하세요^^ Wild Planet 입니다. 잘부탁드립니다. (..) 고고싱        ')
INSERT [dbo].[PLANET_CUSTOM] ([planetName], [planetTheme], [planetTerrain], [planetMemo]) VALUES (N'프레임워크     ', 25, 80002, N'프레임 워크                                            ')
INSERT [dbo].[PLANET_CUSTOM] ([planetName], [planetTheme], [planetTerrain], [planetMemo]) VALUES (N'앵란이는 어디에  ', 40, 80006, N'앵라라라라라라라라라라란!! ;ㅁ;                                ')
INSERT [dbo].[PLANET_CUSTOM] ([planetName], [planetTheme], [planetTerrain], [planetMemo]) VALUES (N'행성이다      ', 51, 80007, N'말말말풍선                                             ')
INSERT [dbo].[PLANET_CUSTOM] ([planetName], [planetTheme], [planetTerrain], [planetMemo]) VALUES (N'제라드       ', 54, 80002, N'제라드의 제라드 행성 임!                                    ')
INSERT [dbo].[PLANET_CUSTOM] ([planetName], [planetTheme], [planetTerrain], [planetMemo]) VALUES (N'이런        ', 55, 80002, N'아쭈구리의 이런 행성 임!                                    ')
INSERT [dbo].[PLANET_CUSTOM] ([planetName], [planetTheme], [planetTerrain], [planetMemo]) VALUES (N'타우농장      ', 56, 80011, N'타우렌함유의 타우농장 행성 임!                                 ')
INSERT [dbo].[PLANET_CUSTOM] ([planetName], [planetTheme], [planetTerrain], [planetMemo]) VALUES (N'기획서용행성    ', 57, 80004, N'안녕하세요^^ Wild Planet입니다. 잘부탁드립니다.                  ')
INSERT [dbo].[PLANET_CUSTOM] ([planetName], [planetTheme], [planetTerrain], [planetMemo]) VALUES (N'주인님차단하세요  ', 58, 80006, N'님이그걸왜먹어여의 주인님차단하세요 행성 임!                          ')
INSERT [dbo].[PLANET_CUSTOM] ([planetName], [planetTheme], [planetTerrain], [planetMemo]) VALUES (N'bone      ', 60, 80008, N'aka의 bone 행성 임!                                   ')
INSERT [dbo].[PLANET_CUSTOM] ([planetName], [planetTheme], [planetTerrain], [planetMemo]) VALUES (N'aaa       ', 61, 80001, N'777의 aaa 행성 임!                                    ')
INSERT [dbo].[PLANET_CUSTOM] ([planetName], [planetTheme], [planetTerrain], [planetMemo]) VALUES (N'test3     ', 62, 80001, N'test3의 test3 행성 임!                                ')
INSERT [dbo].[PLANET_CUSTOM] ([planetName], [planetTheme], [planetTerrain], [planetMemo]) VALUES (N'냐하항       ', 63, 80006, N'test의 냐하항 행성 임!                                   ')
INSERT [dbo].[PLANET_CUSTOM] ([planetName], [planetTheme], [planetTerrain], [planetMemo]) VALUES (N'황소별       ', 64, 80004, N'나밥줘의 황소별 행성 임!                                    ')
INSERT [dbo].[PLANET_CUSTOM] ([planetName], [planetTheme], [planetTerrain], [planetMemo]) VALUES (N'어이쿠야      ', 65, 80008, N'어익쿠의 어이쿠야 행성 임!                                   ')
INSERT [dbo].[PLANET_CUSTOM] ([planetName], [planetTheme], [planetTerrain], [planetMemo]) VALUES (N'나메크성      ', 66, 80008, N'장난감의 나메크성 행성 임!                                   ')
INSERT [dbo].[PLANET_CUSTOM] ([planetName], [planetTheme], [planetTerrain], [planetMemo]) VALUES (N'puchon    ', 67, 80007, N'mOok의 puchon 행성 임!                                ')
INSERT [dbo].[PLANET_CUSTOM] ([planetName], [planetTheme], [planetTerrain], [planetMemo]) VALUES (N'그냥별       ', 68, 80008, N'오쿠샤의 그냥별 행성 임!                                    ')
INSERT [dbo].[PLANET_CUSTOM] ([planetName], [planetTheme], [planetTerrain], [planetMemo]) VALUES (N'QWDQW     ', 69, 80002, N'DREAMEXE의 QWDQW 행성 임!                             ')
INSERT [dbo].[PLANET_CUSTOM] ([planetName], [planetTheme], [planetTerrain], [planetMemo]) VALUES (N'포더호드      ', 70, 80004, N'다덤벼의 포더호드 행성 임!                                   ')
INSERT [dbo].[PLANET_CUSTOM] ([planetName], [planetTheme], [planetTerrain], [planetMemo]) VALUES (N'구구1       ', 71, 80012, N'깜빡했다의 구구1 행성 임!                                   ')
INSERT [dbo].[PLANET_CUSTOM] ([planetName], [planetTheme], [planetTerrain], [planetMemo]) VALUES (N'혹성2b      ', 72, 80012, N'야메의 혹성2b 행성 임!                                    ')
INSERT [dbo].[PLANET_CUSTOM] ([planetName], [planetTheme], [planetTerrain], [planetMemo]) VALUES (N'밥먹자       ', 73, 80002, N'밥은먹고다니니의 밥먹자 행성 임!                                ')
INSERT [dbo].[PLANET_CUSTOM] ([planetName], [planetTheme], [planetTerrain], [planetMemo]) VALUES (N'안드로메다     ', 74, 80001, N'blackhole의 안드로메다 행성 임!                            ')
INSERT [dbo].[PLANET_CUSTOM] ([planetName], [planetTheme], [planetTerrain], [planetMemo]) VALUES (N'공구박스      ', 75, 80009, N'공구함의 공구박스 행성 임!                                   ')
INSERT [dbo].[PLANET_CUSTOM] ([planetName], [planetTheme], [planetTerrain], [planetMemo]) VALUES (N'쨈성        ', 76, 80001, N'째뮌의 쨈성 행성 임!                                      ')
INSERT [dbo].[PLANET_CUSTOM] ([planetName], [planetTheme], [planetTerrain], [planetMemo]) VALUES (N'aa        ', 77, 80008, N'aaa의 aa 행성 임!                                     ')
INSERT [dbo].[PLANET_CUSTOM] ([planetName], [planetTheme], [planetTerrain], [planetMemo]) VALUES (N'달         ', 78, 80003, N'가오리의 달 행성 임!                                      ')
INSERT [dbo].[PLANET_CUSTOM] ([planetName], [planetTheme], [planetTerrain], [planetMemo]) VALUES (N'지구~       ', 80, 80001, N'후훗의 지구~ 행성 임!                                     ')
INSERT [dbo].[PLANET_CUSTOM] ([planetName], [planetTheme], [planetTerrain], [planetMemo]) VALUES (N'네르크란스     ', 82, 80002, N'도라에몽의 네르크란스 행성 임!                                 ')
INSERT [dbo].[PLANET_CUSTOM] ([planetName], [planetTheme], [planetTerrain], [planetMemo]) VALUES (N'qqq       ', 83, 80003, N'ff의 qqq 행성 임!                                     ')
INSERT [dbo].[PLANET_CUSTOM] ([planetName], [planetTheme], [planetTerrain], [planetMemo]) VALUES (N'446       ', 84, 80002, N'asdf의 446 행성 임!                                   ')
INSERT [dbo].[PLANET_CUSTOM] ([planetName], [planetTheme], [planetTerrain], [planetMemo]) VALUES (N'gfgfg     ', 85, 80001, N'fdsfdsf의 gfgfg 행성 임!                              ')
INSERT [dbo].[PLANET_CUSTOM] ([planetName], [planetTheme], [planetTerrain], [planetMemo]) VALUES (N'6666      ', 86, 80007, N'5555의 6666 행성 임!                                  ')
INSERT [dbo].[PLANET_CUSTOM] ([planetName], [planetTheme], [planetTerrain], [planetMemo]) VALUES (N'zxczx     ', 87, 80001, N'dsscsd의 zxczx 행성 임!                               ')
INSERT [dbo].[PLANET_CUSTOM] ([planetName], [planetTheme], [planetTerrain], [planetMemo]) VALUES (N'뽀잉        ', 88, 80012, N'뿌잉의 뽀잉 행성 임!                                      ')
INSERT [dbo].[PLANET_CUSTOM] ([planetName], [planetTheme], [planetTerrain], [planetMemo]) VALUES (N'쥬신의별      ', 89, 80001, N'기하의 쥬신의별 행성 임!                                    ')
INSERT [dbo].[PLANET_CUSTOM] ([planetName], [planetTheme], [planetTerrain], [planetMemo]) VALUES (N'ddf       ', 90, 80008, N'aaaaaf의 ddf 행성 임!                                 ')
INSERT [dbo].[PLANET_CUSTOM] ([planetName], [planetTheme], [planetTerrain], [planetMemo]) VALUES (N'스튜디오뮤트    ', 91, 80011, N'스튜디오뮤트 홧팅                                         ')
INSERT [dbo].[PLANET_CUSTOM] ([planetName], [planetTheme], [planetTerrain], [planetMemo]) VALUES (N'옴니        ', 92, 80005, N'뽀오의 옴니 행성 임!                                      ')
INSERT [dbo].[PLANET_CUSTOM] ([planetName], [planetTheme], [planetTerrain], [planetMemo]) VALUES (N'팡팡게루      ', 93, 80005, N'팡케루의 팡팡게루 행성 임!                                   ')
INSERT [dbo].[PLANET_CUSTOM] ([planetName], [planetTheme], [planetTerrain], [planetMemo]) VALUES (N'moya      ', 94, 80001, N'xkall의 moya 행성 임!                                 ')
INSERT [dbo].[PLANET_CUSTOM] ([planetName], [planetTheme], [planetTerrain], [planetMemo]) VALUES (N'Goat      ', 95, 80012, N'푸르푸르의 Goat 행성 임!                                  ')
INSERT [dbo].[PLANET_CUSTOM] ([planetName], [planetTheme], [planetTerrain], [planetMemo]) VALUES (N'444       ', 96, 80001, N'666의 444 행성 임!                                    ')
INSERT [dbo].[PLANET_CUSTOM] ([planetName], [planetTheme], [planetTerrain], [planetMemo]) VALUES (N'별이        ', 121, 80002, N'NHN에 가고 싶어욤                                       ')
INSERT [dbo].[PLANET_CUSTOM] ([planetName], [planetTheme], [planetTerrain], [planetMemo]) VALUES (N'염소        ', 49, 80012, N'qwer의 염소 행성 임!                                    ')
INSERT [dbo].[PLANET_CUSTOM] ([planetName], [planetTheme], [planetTerrain], [planetMemo]) VALUES (N'123       ', 97, 80004, N'가라가라가                                             ')
INSERT [dbo].[PLANET_CUSTOM] ([planetName], [planetTheme], [planetTerrain], [planetMemo]) VALUES (N'fef       ', 99, 80002, N'ds의 fef 행성 임!                                     ')
INSERT [dbo].[PLANET_CUSTOM] ([planetName], [planetTheme], [planetTerrain], [planetMemo]) VALUES (N'안녕하세요     ', 100, 80008, N'와일드플래닛의 안녕하세요 행성 임!                               ')
INSERT [dbo].[PLANET_CUSTOM] ([planetName], [planetTheme], [planetTerrain], [planetMemo]) VALUES (N'내꺼        ', 102, 80003, N'테스트용의 내꺼 행성 임!                                    ')
INSERT [dbo].[PLANET_CUSTOM] ([planetName], [planetTheme], [planetTerrain], [planetMemo]) VALUES (N'qweqwe    ', 103, 80006, N'asd의 qweqwe 행성 임!                                 ')
INSERT [dbo].[PLANET_CUSTOM] ([planetName], [planetTheme], [planetTerrain], [planetMemo]) VALUES (N'SAM       ', 105, 80011, N'SAM의 별에 오신것을 환영합니다^^                              ')
INSERT [dbo].[PLANET_CUSTOM] ([planetName], [planetTheme], [planetTerrain], [planetMemo]) VALUES (N'ss        ', 106, 80004, N'ss의 ss 행성 임!                                      ')
INSERT [dbo].[PLANET_CUSTOM] ([planetName], [planetTheme], [planetTerrain], [planetMemo]) VALUES (N'루나의 행성    ', 107, 80001, N'                                                  ')
INSERT [dbo].[PLANET_CUSTOM] ([planetName], [planetTheme], [planetTerrain], [planetMemo]) VALUES (N'카라        ', 108, 80010, N'한승연의 카라 행성 임!                                     ')
INSERT [dbo].[PLANET_CUSTOM] ([planetName], [planetTheme], [planetTerrain], [planetMemo]) VALUES (N'피콜로제국     ', 110, 80004, N'얄리몬의 피콜로제국 행성 임!                                  ')
INSERT [dbo].[PLANET_CUSTOM] ([planetName], [planetTheme], [planetTerrain], [planetMemo]) VALUES (N'1         ', 111, 80007, N'1의 1 행성 임!                                        ')
INSERT [dbo].[PLANET_CUSTOM] ([planetName], [planetTheme], [planetTerrain], [planetMemo]) VALUES (N'ppp       ', 114, 80006, N'말풍선 커스터마이즈                                        ')
INSERT [dbo].[PLANET_CUSTOM] ([planetName], [planetTheme], [planetTerrain], [planetMemo]) VALUES (N'pppp의 행성  ', 116, 80003, N'pppp의 pppp의 행성 행성 임!                              ')
INSERT [dbo].[PLANET_CUSTOM] ([planetName], [planetTheme], [planetTerrain], [planetMemo]) VALUES (N'내 행성      ', 118, 80003, N'ppppp의 내 행성 행성 임!                                 ')
INSERT [dbo].[PLANET_CUSTOM] ([planetName], [planetTheme], [planetTerrain], [planetMemo]) VALUES (N'미순        ', 120, 80003, N'미순의 미순 행성 임!                                      ')
INSERT [dbo].[PLANET_CUSTOM] ([planetName], [planetTheme], [planetTerrain], [planetMemo]) VALUES (N'MEMORY    ', 122, 80005, N'KGDA행성                                            ')
INSERT [dbo].[PLANET_CUSTOM] ([planetName], [planetTheme], [planetTerrain], [planetMemo]) VALUES (N'virtual   ', 123, 80007, N'클스의 virtual 행성 임!                                 ')
INSERT [dbo].[PLANET_CUSTOM] ([planetName], [planetTheme], [planetTerrain], [planetMemo]) VALUES (N'adad      ', 124, 80003, N'asdd의 adad 행성 임!                                  ')
INSERT [dbo].[PLANET_CUSTOM] ([planetName], [planetTheme], [planetTerrain], [planetMemo]) VALUES (N'dwd       ', 125, 80001, N'ddwee의 dwd 행성 임!                                  ')
/****** Object:  StoredProcedure [dbo].[usp_DeleteAvatarInven]    Script Date: 10/29/2018 19:50:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
---------------------------
-- 객체이름 : dbo.usp_DeleteAvatarInven
-- 파라미터 : @pmTable NCHAR(10), @pmNum INT
-- 제작자 : baboruri
-- 제작일 : 09-06-01
-- 변경일 : 
-- 내용 : 인벤에 추가하기.
-- 결과
-- 성공 Return : 0;
-- 실패 Return : 1;
---------------------------
CREATE PROCEDURE [dbo].[usp_DeleteAvatarInven]
	@pmTable		NCHAR(10),
	@pmNum		INT
AS
	SET NOCOUNT ON

	IF( N'TYPE' = @pmTable )
		BEGIN
			DELETE INVEN_TYPE WHERE invenNum = @pmNum
	 	END
	ELSE IF( N'COLOR' = @pmTable)
		BEGIN
			DELETE INVEN_COLOR WHERE invenNum = @pmNum
		END
	ELSE IF( N'HEAD' = @pmTable )
		BEGIN
			DELETE INVEN_HEAD WHERE invenNum = @pmNum
		END
	ELSE IF( N'BODY' = @pmTable )
		BEGIN
			DELETE INVEN_BODY WHERE invenNum = @pmNum
		END
	ELSE
		BEGIN
			RETURN 1;
		END
		
	RETURN 0;
GO
/****** Object:  StoredProcedure [dbo].[usp_DeletePlanetInven]    Script Date: 10/29/2018 19:50:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
---------------------------
-- 객체이름 : dbo.usp_DeletePlanetInven
-- 파라미터 : @pmTable NCHAR(10), @pmNum INT
-- 제작자 : baboruri
-- 제작일 : 09-06-04
-- 변경일 : 
-- 내용 : 인벤에 추가하기.
-- 결과
-- 성공 Return : 0;
-- 실패 Return : 1;
---------------------------
CREATE PROCEDURE [dbo].[usp_DeletePlanetInven]
	@pmTable		NCHAR(10),
	@pmNum		INT
AS
	SET NOCOUNT ON

	IF( N'THEME' = @pmTable )
		BEGIN
			DELETE INVEN_THEME WHERE invenNum = @pmNum
	 	END
	ELSE IF( N'OBJECT' = @pmTable)
		BEGIN
			DELETE INVEN_OBJECT WHERE invenNum = @pmNum
		END
	ELSE
		BEGIN
			RETURN 1;
		END
		
	RETURN 0;
GO
/****** Object:  StoredProcedure [dbo].[usp_GetAvatarInven]    Script Date: 10/29/2018 19:50:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
---------------------------
-- 객체이름 : dbo.usp_GetAvatarInven
-- 파라미터 : @pmTable NCHAR(10), @pmName NCHAR(10)
-- 제작자 : baboruri
-- 제작일 : 09-06-01
-- 변경일 : 
-- 내용 : 인벤 얻어오기.
-- 결과
-- 성공 Return : 0;
-- 실패 Return : 1;
---------------------------
CREATE PROCEDURE [dbo].[usp_GetAvatarInven]
	@pmTable		NCHAR(10),
	@pmName		NCHAR(10)
AS
	SET NOCOUNT ON
	
	IF( N'TYPE' = @pmTable )
		BEGIN
			SELECT invenNum, itemCode, itemUse	FROM INVEN_TYPE	WHERE characterName = @pmName
 		END
	ELSE IF( N'COLOR' = @pmTable)
		BEGIN
			SELECT invenNum, itemCode, itemUse	FROM INVEN_COLOR WHERE characterName = @pmName
		END
	ELSE IF( N'HEAD' = @pmTable )
		BEGIN
			SELECT invenNum, itemCode, itemUse	FROM INVEN_HEAD WHERE characterName = @pmName
		END
	ELSE IF( N'BODY' = @pmTable )
		BEGIN
			SELECT invenNum, itemCode, itemUse	FROM INVEN_BODY WHERE characterName = @pmName
		END
	ELSE
		BEGIN
			RETURN 1;
		END
	
	RETURN 0;
GO
/****** Object:  StoredProcedure [dbo].[usp_GetFriendList]    Script Date: 10/29/2018 19:50:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
---------------------------
-- 객체이름 : dbo.usp_GetFriendList
-- 파라미터 : @pmName NCHAR(10)
-- 제작자 : baboruri
-- 제작일 : 09-06-01
-- 변경일 : 
-- 내용 : 친구목록 얻어오기
-- 결과
-- 성공 Return : 0;
---------------------------
CREATE PROCEDURE [dbo].[usp_GetFriendList]
	@pmName	NCHAR(10)
AS
	SET NOCOUNT ON
	
	SELECT RTRIM(fName)
	FROM FRIEND_LIST
	WHERE characterName = @pmName
	
	RETURN 0
GO
/****** Object:  StoredProcedure [dbo].[usp_GetPlanetInven]    Script Date: 10/29/2018 19:50:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
---------------------------
-- 객체이름 : dbo.usp_GetPlanetInven
-- 파라미터 : @pmTable NCHAR(10), @pmName NCHAR(10)
-- 제작자 : baboruri
-- 제작일 : 09-06-01
-- 변경일 : 
-- 내용 : 인벤 얻어오기.
-- 결과
-- 성공 Return : 0;
-- 실패 Return : 1;
---------------------------
CREATE PROCEDURE [dbo].[usp_GetPlanetInven]
	@pmTable		NCHAR(10),
	@pmName		NCHAR(10)
AS
	SET NOCOUNT ON
	
	IF( N'THEME' = @pmTable )
		BEGIN
			SELECT invenNum, itemCode, itemUse	FROM INVEN_THEME WHERE characterName = @pmName
 		END
	ELSE IF( N'OBJECT' = @pmTable)
		BEGIN
			SELECT invenNum, itemCode, itemUse	FROM INVEN_OBJECT WHERE characterName = @pmName
		END
	ELSE
		BEGIN
			RETURN 1;
		END
	
	RETURN 0;
GO
/****** Object:  StoredProcedure [dbo].[usp_GetRanking]    Script Date: 10/29/2018 19:50:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
---------------------------
-- 객체이름 : dbo.usp_GetRanking
-- 파라미터 :
-- 제작자 : baboruri
-- 제작일 : 09-06-19
-- 변경일 : 
-- 내용 : 랭킹 얻어오기.
-- 결과
-- 성공 Return : 0;
---------------------------
CREATE PROCEDURE [dbo].[usp_GetRanking]
AS
	SET NOCOUNT ON
	
	SELECT TOP 10 RTRIM(characterName), exper
	FROM RANKING
	ORDER BY exper DESC
	
	RETURN 0;
GO
/****** Object:  StoredProcedure [dbo].[usp_SetPlanetInvenUse]    Script Date: 10/29/2018 19:50:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
---------------------------
-- 객체이름 : dbo.usp_SetPlanetInvenUse
-- 파라미터 : @pmTable NCHAR(10), @pmNum INT, @pmItemUse BIT
-- 제작자 : baboruri
-- 제작일 : 09-06-01
-- 변경일 : 
-- 내용 : 아이템 사용 변경하기.
-- 결과
-- 성공 Return : 0;
-- 실패 Return : 1;
---------------------------
CREATE PROCEDURE [dbo].[usp_SetPlanetInvenUse]
	@pmTable		NCHAR(10),
	@pmNum		INT,
	@pmItemUse	BIT
AS
	SET NOCOUNT ON
	
	IF( N'THEME' = @pmTable )
		BEGIN
			UPDATE INVEN_THEME SET itemUse = @pmItemUse WHERE invenNum = @pmNum
 		END
	ELSE IF( N'OBJECT' = @pmTable)
		BEGIN
			UPDATE INVEN_OBJECT SET itemUse = @pmItemUse WHERE invenNum = @pmNum
		END
	ELSE
		BEGIN
			RETURN 1;
		END
	
	RETURN 0;
GO
/****** Object:  StoredProcedure [dbo].[usp_SetFriendList]    Script Date: 10/29/2018 19:50:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
---------------------------
-- 객체이름 : dbo.usp_SetFriendList
-- 파라미터 : @pmName NCHAR(10), @pmFList NCHAR(10)
-- 제작자 : baboruri
-- 제작일 : 09-06-01
-- 변경일 : 
-- 내용 : 친구목록 추가하기.
-- 결과
-- 성공 Return : 0;
---------------------------
CREATE PROCEDURE [dbo].[usp_SetFriendList]
	@pmName	NCHAR(10),
	@pmFName	NCHAR(10)
AS
	SET NOCOUNT ON
	
	BEGIN TRY
	BEGIN TRAN
		INSERT INTO FRIEND_LIST( characterName, fName )
			VALUES( @pmName, @pmFName )
		COMMIT TRAN
		RETURN 0;		
	END TRY
	
	BEGIN CATCH
		ROLLBACK;
		RETURN 1;
	END CATCH
GO
/****** Object:  StoredProcedure [dbo].[usp_GetPlanet]    Script Date: 10/29/2018 19:50:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
---------------------------
-- 객체이름 : dbo.usp_GetPlanet
-- 파라미터 : @pmCName NCHAR(10), @pmPName NVARCHAR(10) OUTPUT
-- 제작자 : baboruri
-- 제작일 : 09-06-04
-- 변경일 : 
-- 내용 : 행성 이름 얻어오기
-- 결과
-- 성공 Return : 0;
---------------------------
CREATE PROCEDURE [dbo].[usp_GetPlanet]
	@pmCName		NCHAR(10),
	@pmPName		NVARCHAR(10) OUTPUT
AS
	SET NOCOUNT ON
	
	SELECT @pmPName = RTRIM(planetName)
	FROM PLANET_BASE
	WHERE characterName = @pmCName
	
	RETURN 0;
GO
/****** Object:  StoredProcedure [dbo].[usp_SetAvatarInvenUse]    Script Date: 10/29/2018 19:50:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
---------------------------
-- 객체이름 : dbo.usp_SetAvatarInvenUse
-- 파라미터 : @pmTable NCHAR(10), @pmNum INT, @pmItemUse BIT
-- 제작자 : baboruri
-- 제작일 : 09-06-01
-- 변경일 : 
-- 내용 : 아이템 사용 변경하기.
-- 결과
-- 성공 Return : 0;
-- 실패 Return : 1;
---------------------------
CREATE PROCEDURE [dbo].[usp_SetAvatarInvenUse]
	@pmTable		NCHAR(10),
	@pmNum		INT,
	@pmItemUse	BIT
AS
	SET NOCOUNT ON
	
	IF( N'TYPE' = @pmTable )
		BEGIN
			UPDATE INVEN_TYPE SET itemUse = @pmItemUse	WHERE invenNum = @pmNum
 		END
	ELSE IF( N'COLOR' = @pmTable)
		BEGIN
			UPDATE INVEN_COLOR SET itemUse = @pmItemUse	WHERE invenNum = @pmNum
		END
	ELSE IF( N'HEAD' = @pmTable )
		BEGIN
			UPDATE INVEN_HEAD SET itemUse = @pmItemUse	WHERE invenNum = @pmNum
		END
	ELSE IF( N'BODY' = @pmTable )
		BEGIN
			UPDATE INVEN_BODY SET itemUse = @pmItemUse	WHERE invenNum = @pmNum
		END
	ELSE
		BEGIN
			RETURN 1;
		END
	
	RETURN 0;
GO
/****** Object:  StoredProcedure [dbo].[usp_TradeObject]    Script Date: 10/29/2018 19:50:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
---------------------------
-- 객체이름 : dbo.usp_TradeObject
-- 파라미터 : @characterName NCHAR(10), @itemCode INT, @dealMode TINYINT, @price INT
-- 제작자 : baboruri
-- 제작일 : 09-06-02
-- 변경일 : 
-- 내용 : 거래 모드 추가.
-- 결과
-- 생생에 성공 Return : 0;
---------------------------
CREATE PROCEDURE [dbo].[usp_TradeObject]
	@pmCharacterName	NCHAR(10),
	@pmItemCode			INT,
	@pmDealMode			TINYINT
AS
	SET NOCOUNT ON
	
	INSERT INTO TRADE_OBJECT( characterName, itemCode, dealMode, buyTime )
	VALUES( @pmCharacterName, @pmItemCode, @pmDealMode, default )
GO
/****** Object:  StoredProcedure [dbo].[usp_TradeAvatar]    Script Date: 10/29/2018 19:50:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
---------------------------
-- 객체이름 : dbo.usp_TradeAvatar
-- 파라미터 : @characterName NCHAR(10), @itemCode INT, @dealMode TINYINT, @price INT
-- 제작자 : baboruri
-- 제작일 : 09-06-02
-- 변경일 : 
-- 내용 : 거래 모드 추가.
-- 결과
-- 생생에 성공 Return : 0;
---------------------------
CREATE PROCEDURE [dbo].[usp_TradeAvatar]
	@pmCharacterName	NCHAR(10),
	@pmItemCode			INT,
	@pmDealMode			TINYINT
AS
	SET NOCOUNT ON
	
	INSERT INTO TRADE_AVATAR( characterName, itemCode, dealMode, buyTime )
	VALUES( @pmCharacterName, @pmItemCode, @pmDealMode, default )
GO
/****** Object:  StoredProcedure [dbo].[usp_SetPlanetTheme]    Script Date: 10/29/2018 19:50:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
---------------------------
-- 객체이름 : dbo.usp_SetPlanetTheme
-- 파라미터 : @pmPName NCHAR(10), @pmTheme INT, @pmOldTheme INT = 0
-- 제작자 : baboruri
-- 제작일 : 09-06-04
-- 변경일 : 
-- 내용 : 행성 테마 변경하기.
-- 결과
-- 성공 Return : 0;
---------------------------
CREATE PROCEDURE [dbo].[usp_SetPlanetTheme]
	@pmPName NCHAR(10),
	@pmNewTheme INT,
	@pmOldTheme INT = 0
AS
	SET NOCOUNT ON
	
	UPDATE PLANET_CUSTOM
	SET planetTheme = @pmNewTheme
	WHERE planetName = @pmPName
	
	
	EXECUTE WildPlanetDB.dbo.usp_SetPlanetInvenUse N'THEME', @pmNewTheme, 1
	
	IF( @pmOldTheme > 0 )
		BEGIN
			EXECUTE WildPlanetDB.dbo.usp_SetPlanetInvenUse N'THEME', @pmOldTheme, 0
		END
		
	RETURN 0;
GO
/****** Object:  StoredProcedure [dbo].[usp_SetPlanetMemo]    Script Date: 10/29/2018 19:50:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
---------------------------
-- 객체이름 : dbo.usp_SetPlanetMemo
-- 파라미터 : @pmMemo NCHAR(50)
-- 제작자 : baboruri
-- 제작일 : 09-06-04
-- 변경일 : 
-- 내용 : 행성 메모 변경하기.
-- 결과
-- 성공 Return : 0;
---------------------------
CREATE PROCEDURE [dbo].[usp_SetPlanetMemo]
	@pmPName NCHAR(10),
	@pmMemo NCHAR(50)
AS
	SET NOCOUNT ON
	
	UPDATE PLANET_CUSTOM
	SET planetMemo = @pmMemo
	WHERE planetName = @pmPName
	
	RETURN 0;
GO
/****** Object:  StoredProcedure [dbo].[usp_SetCharCustomType]    Script Date: 10/29/2018 19:50:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
---------------------------
-- 객체이름 : dbo.usp_SetCharCustomType
-- 파라미터 : @pmName	NCHAR(10), @pmNewType INT, @pmOldType INT = 0
-- 제작자 : baboruri
-- 제작일 : 09-06-01
-- 변경일 : 
-- 내용 : 케릭터 커스터마이징 - 타입 바꾸기.
-- 결과
-- 성공 Return : 0;
---------------------------
CREATE PROCEDURE [dbo].[usp_SetCharCustomType]
	@pmName	NCHAR(10),
	@pmNewType	INT,
	@pmOldType	INT = 0
AS
	SET NOCOUNT ON
		
	-- 변경하려고 하는 아이템의 유효성 검사는 서버에서 하자.
	UPDATE CHARACTER_CUSTOM
	SET characterType = @pmNewType
	WHERE characterName = @pmName
	
	EXECUTE WildPlanetDB.dbo.usp_SetAvatarInvenUse N'TYPE', @pmNewType, 1
	
	IF( @pmOldType > 0 )
		BEGIN
			EXECUTE WildPlanetDB.dbo.usp_SetAvatarInvenUse N'TYPE', @pmOldType, 0
		END
	
	RETURN 0;
GO
/****** Object:  StoredProcedure [dbo].[usp_SetCharCustomHead]    Script Date: 10/29/2018 19:50:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
---------------------------
-- 객체이름 : dbo.usp_SetCharCustomHead
-- 파라미터 :	@pmName	NCHAR(10), @pmNewHead INT, @pmOldHead INT = 0
-- 제작자 : baboruri
-- 제작일 : 09-06-01
-- 변경일 : 
-- 내용 : 케릭터 커스터마이징 - 머리 바꾸기.
-- 결과
-- 성공 Return : 0;
---------------------------
CREATE PROCEDURE [dbo].[usp_SetCharCustomHead]
	@pmName	NCHAR(10),
	@pmNewHead	INT,
	@pmOldHead	INT = 0
AS
	SET NOCOUNT ON
		
	-- 변경하려고 하는 아이템의 유효성 검사는 서버에서 하자.
	UPDATE CHARACTER_CUSTOM
	SET characterHead = @pmNewHead
	WHERE characterName = @pmName
	
	EXECUTE WildPlanetDB.dbo.usp_SetAvatarInvenUse N'HEAD', @pmNewHead, 1
	
	IF( @pmOldHead > 0 )
		BEGIN
			EXECUTE WildPlanetDB.dbo.usp_SetAvatarInvenUse N'HEAD', @pmOldHead, 0
		END
	
	RETURN 0;
GO
/****** Object:  StoredProcedure [dbo].[usp_SetCharCustomColor]    Script Date: 10/29/2018 19:50:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
---------------------------
-- 객체이름 : dbo.usp_SetCharCustomColor
-- 파라미터 : @pmName	NCHAR(10), @@pmNewColor INT, @@pmOldColor INT = 0
-- 제작자 : baboruri
-- 제작일 : 09-06-01
-- 변경일 : 
-- 내용 : 케릭터 커스터마이징 - 색 바꾸기.
-- 결과
-- 성공 Return : 0;
---------------------------
CREATE PROCEDURE [dbo].[usp_SetCharCustomColor]
	@pmName	NCHAR(10),
	@pmNewColor	INT,
	@pmOldColor	INT = 0
AS
	SET NOCOUNT ON
		
	-- 변경하려고 하는 아이템의 유효성 검사는 서버에서 하자.
	UPDATE CHARACTER_CUSTOM
	SET characterColor = @pmNewColor
	WHERE characterName = @pmName
	
	EXECUTE WildPlanetDB.dbo.usp_SetAvatarInvenUse N'COLOR', @pmNewColor, 1
	
	IF( @pmOldColor > 0 )
		BEGIN
			EXECUTE WildPlanetDB.dbo.usp_SetAvatarInvenUse N'COLOR', @pmOldColor, 0
		END
	
	RETURN 0;
GO
/****** Object:  StoredProcedure [dbo].[usp_SetCharCustomBody]    Script Date: 10/29/2018 19:50:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
---------------------------
-- 객체이름 : dbo.usp_SetCharCustomBody
-- 파라미터 : @pmName	NCHAR(10), @pmNewBody INT, @pmOldBody INT = 0
-- 제작자 : baboruri
-- 제작일 : 09-06-01
-- 변경일 : 
-- 내용 : 케릭터 커스터마이징 - 바디 바꾸기.
-- 결과
-- 성공 Return : 0;
---------------------------
CREATE PROCEDURE [dbo].[usp_SetCharCustomBody]
	@pmName	NCHAR(10),
	@pmNewBody	INT,
	@pmOldBody	INT = 0
AS
	SET NOCOUNT ON
		
	-- 변경하려고 하는 아이템의 유효성 검사는 서버에서 하자.
	UPDATE CHARACTER_CUSTOM
	SET characterBody = @pmNewBody
	WHERE characterName = @pmName
	
	EXECUTE WildPlanetDB.dbo.usp_SetAvatarInvenUse N'BODY', @pmNewBody, 1
	
	IF( @pmOldBody > 0 )
		BEGIN
			EXECUTE WildPlanetDB.dbo.usp_SetAvatarInvenUse N'BODY', @pmOldBody, 0
		END
	
	RETURN 0;
GO
/****** Object:  StoredProcedure [dbo].[usp_InsertPlanetObject]    Script Date: 10/29/2018 19:50:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
---------------------------
-- 객체이름 : dbo.usp_InsertPlanetObject
-- 파라미터 : @pmPName NCHAR(10), @pmObjInvenNum INT, @pmTileNum SMALLINT
-- 제작자 : baboruri
-- 제작일 : 09-06-04
-- 변경일 : 
-- 내용 : 행성에 오브젝트 추가하기.
-- 결과
-- 성공 Return : 0;
-- 실패 Return : 1;
---------------------------
CREATE PROCEDURE [dbo].[usp_InsertPlanetObject]
	@pmPName			NCHAR(10),
	@pmObjInvenNum	INT,
	@pmTileNum		SMALLINT
AS
	SET NOCOUNT ON

	BEGIN TRY
		BEGIN TRAN
			INSERT INTO PLANET_OBJECT( planetName, objectNum, tileNum )
			VALUES( @pmPName, @pmObjInvenNum, @pmTileNum )
			
			EXECUTE WildPlanetDB.dbo.usp_SetPlanetInvenUse N'OBJECT', @pmObjInvenNum, 1
		COMMIT TRAN			
		RETURN 0;
	END TRY
		
	BEGIN CATCH
		ROLLBACK
		RETURN 1;	
	END CATCH
GO
/****** Object:  StoredProcedure [dbo].[usp_InsertPlanetInven]    Script Date: 10/29/2018 19:50:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
---------------------------
-- 객체이름 : dbo.usp_InsertPlanetInven
-- 파라미터 : @pmTable NCHAR(10), @pmName NCHAR(10), @pmNum INT OUTPUT, @pmItemCode INT, @pmItemUse BIT
-- 제작자 : baboruri
-- 제작일 : 09-06-04
-- 변경일 : 
-- 내용 : 인벤에 추가하기.
-- 결과
-- 성공 Return : 0;
-- 실패 Return : 1;
---------------------------
CREATE PROCEDURE [dbo].[usp_InsertPlanetInven]
	@pmTable		NCHAR(10),
	@pmName		NCHAR(10),
	@pmNum		INT OUTPUT,
	@pmItemCode	INT,
	@pmDealMode	TINYINT,
	@pmItemUse	BIT	 = 0
AS
	SET NOCOUNT ON

	BEGIN TRY
		BEGIN TRAN
			IF( N'THEME' = @pmTable )
				BEGIN
					INSERT INTO INVEN_THEME( characterName, itemCode, itemUse ) VALUES( @pmName, @pmItemCode, @pmItemUse )
		 		END
			ELSE IF( N'OBJECT' = @pmTable)
				BEGIN
					INSERT INTO INVEN_OBJECT( characterName, itemCode, itemUse ) VALUES( @pmName, @pmItemCode, @pmItemUse )
				END		
			ELSE
				BEGIN
					RETURN 2;
				END
			
			SELECT @pmNum = @@IDENTITY
			
			EXECUTE WildPlanetDB.dbo.usp_TradeObject @pmName, @pmItemCode, @pmDealMode
		COMMIT TRAN
				
		RETURN 0;
	END TRY
		
	BEGIN CATCH
		RETURN 1;	
	END CATCH
GO
/****** Object:  StoredProcedure [dbo].[usp_InsertAvatarInven]    Script Date: 10/29/2018 19:50:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
---------------------------
-- 객체이름 : dbo.usp_InsertInven
-- 파라미터 : @pmTable NCHAR(10), @pmName NCHAR(10), @pmNum INT OUTPUT, @pmItemCode INT, @pmItemUse BIT
-- 제작자 : baboruri
-- 제작일 : 09-06-01
-- 변경일 : 
-- 내용 : 인벤에 추가하기.
-- 결과
-- 성공 Return : 0;
-- 실패 Return : 1;
---------------------------
CREATE PROCEDURE [dbo].[usp_InsertAvatarInven]
	@pmTable		NCHAR(10),
	@pmName		NCHAR(10),
	@pmNum		INT OUTPUT,
	@pmItemCode	INT,
	@pmDealMode	TINYINT,
	@pmItemUse	BIT	 = 0
AS
	SET NOCOUNT ON

	BEGIN TRY
		IF( N'TYPE' = @pmTable )
			BEGIN
		 		INSERT INTO INVEN_TYPE( characterName, itemCode, itemUse ) VALUES( @pmName, @pmItemCode, @pmItemUse )
		 	END
		ELSE IF( N'COLOR' = @pmTable)
			BEGIN
				INSERT INTO INVEN_COLOR( characterName, itemCode, itemUse ) VALUES( @pmName, @pmItemCode, @pmItemUse )
			END
		ELSE IF( N'HEAD' = @pmTable )
			BEGIN
				INSERT INTO INVEN_HEAD( characterName, itemCode, itemUse ) VALUES( @pmName, @pmItemCode, @pmItemUse )
			END
		ELSE IF( N'BODY' = @pmTable )
			BEGIN
				INSERT INTO INVEN_BODY( characterName, itemCode, itemUse ) VALUES( @pmName, @pmItemCode, @pmItemUse )
			END
		ELSE
			BEGIN
				RETURN 2;
			END
			
		SELECT @pmNum = @@IDENTITY
		
		EXECUTE WildPlanetDB.dbo.usp_TradeAvatar @pmName, @pmItemCode, @pmDealMode
				
		RETURN 0;
	END TRY
		
	BEGIN CATCH
		RETURN 1;	
	END CATCH
GO
/****** Object:  StoredProcedure [dbo].[usp_GetPlanetObject]    Script Date: 10/29/2018 19:50:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
---------------------------
-- 객체이름 : dbo.usp_GetPlanetObject
-- 파라미터 : @pmTable NCHAR(10), @pmName NCHAR(10)
-- 제작자 : baboruri
-- 제작일 : 09-06-04
-- 변경일 : 
-- 내용 : 오브젝트들 얻어오기.
-- 결과
-- 성공 Return : 0;
---------------------------
CREATE PROCEDURE [dbo].[usp_GetPlanetObject]
	@pmPName		NCHAR(10)
AS
	SET NOCOUNT ON
	
	--SELECT objectNum, tileNum
	--FROM PLANET_OBJECT
	--WHERE planetName = @pmPName
		
	SELECT INVEN_OBJECT.itemCode, INVEN_OBJECT.invenNum, PLANET_OBJECT.tileNum
	FROM PLANET_OBJECT
		LEFT JOIN INVEN_OBJECT
	ON PLANET_OBJECT.objectNum = INVEN_OBJECT.invenNum
	WHERE PLANET_OBJECT.planetName = @pmPName
	
	RETURN 0;
GO
/****** Object:  StoredProcedure [dbo].[usp_GetPlanetCustom]    Script Date: 10/29/2018 19:50:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
---------------------------
-- 객체이름 : dbo.usp_GetPlanetCustom
-- 파라미터 : @pmPName NCHAR(10), @pmTheme INT OUTPUT, @pmTerrain INT OUTPUT, @pmMemo NVARCHAR(50) OUTPUT
-- 제작자 : baboruri
-- 제작일 : 09-06-04
-- 변경일 : 
-- 내용 : 커스텀 얻어오기.
-- 결과
-- 성공 Return : 0;
---------------------------
CREATE PROCEDURE [dbo].[usp_GetPlanetCustom]
	@pmPName		NCHAR(10),
	@pmTheme		INT OUTPUT,
	@pmTerrain		INT OUTPUT,
	@pmMemo		NVARCHAR(50) OUTPUT
AS
	SET NOCOUNT ON
		
	SELECT @pmTheme = INVEN_THEME.itemCode, @pmTerrain = PLANET_CUSTOM.planetTerrain, @pmMemo = RTRIM(PLANET_CUSTOM.planetMemo)
	FROM PLANET_CUSTOM
		LEFT JOIN INVEN_THEME
	ON PLANET_CUSTOM.planetTheme = INVEN_THEME.invenNum
	WHERE PLANET_CUSTOM.planetName = @pmPName
	
	RETURN 0;
GO
/****** Object:  StoredProcedure [dbo].[usp_GetCharacterCustom]    Script Date: 10/29/2018 19:50:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
---------------------------
-- 객체이름 : dbo.GetCharacterCustom
-- 파라미터 : @pmName	NCHAR(10), @pmType	INT OUTPUT,	@pmColor	INT OUTPUT, @pmHead	INT OUTPUT, @pmBody	INT OUTPUT
-- 제작자 : baboruri
-- 제작일 : 09-06-01
-- 변경일 : 
-- 내용 : 케릭터 커스터마이징 얻어오기.
-- 결과
-- 성공 Return : 0;
---------------------------
CREATE PROCEDURE [dbo].[usp_GetCharacterCustom]
	@pmName	NCHAR(10),
	@pmType	INT OUTPUT,
	@pmColor	INT OUTPUT,
	@pmHead	INT OUTPUT,
	@pmBody	INT OUTPUT
AS
	SET NOCOUNT ON
	
	--SELECT @pmType = characterType, @pmColor = characterColor, @pmHead = characterHead, @pmBody = characterBody
	--FROM CHARACTER_CUSTOM
	--WHERE characterName = @pmName
	
	SELECT @pmType = INVEN_TYPE.itemCode
	FROM CHARACTER_CUSTOM
		LEFT JOIN INVEN_TYPE
	ON CHARACTER_CUSTOM.characterType = INVEN_TYPE.invenNum
	WHERE CHARACTER_CUSTOM.characterName = @pmName
	
	SELECT @pmColor = INVEN_COLOR.itemCode
	FROM CHARACTER_CUSTOM
		LEFT JOIN INVEN_COLOR
	ON CHARACTER_CUSTOM.characterColor = INVEN_COLOR.invenNum
	WHERE CHARACTER_CUSTOM.characterName = @pmName
	
	SELECT @pmHead = INVEN_HEAD.itemCode
	FROM CHARACTER_CUSTOM
		LEFT JOIN INVEN_HEAD
	ON CHARACTER_CUSTOM.characterHead = INVEN_HEAD.invenNum
	WHERE CHARACTER_CUSTOM.characterName = @pmName
		
	SELECT @pmBody = INVEN_BODY.itemCode
	FROM CHARACTER_CUSTOM
		LEFT JOIN INVEN_BODY
	ON CHARACTER_CUSTOM.characterBody = INVEN_BODY.invenNum
	WHERE CHARACTER_CUSTOM.characterName = @pmName
		
	RETURN 0;
GO
/****** Object:  StoredProcedure [dbo].[usp_DeletePlanetObject]    Script Date: 10/29/2018 19:50:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
---------------------------
-- 객체이름 : dbo.usp_DeletePlanetObject
-- 파라미터 : @pmObjInvenNum	INT
-- 제작자 : baboruri
-- 제작일 : 09-06-04
-- 변경일 : 
-- 내용 : 행성에 오브젝트 제거하기.
-- 결과
-- 성공 Return : 0;
---------------------------
CREATE PROCEDURE [dbo].[usp_DeletePlanetObject]
	@pmObjInvenNum	INT
AS
	SET NOCOUNT ON

	DELETE PLANET_OBJECT
	WHERE objectNum = @pmObjInvenNum
	
	DELETE INVEN_OBJECT
	WHERE invenNum = @pmObjInvenNum
			
	RETURN 0;
GO
/****** Object:  StoredProcedure [dbo].[usp_CreatePlanet]    Script Date: 10/29/2018 19:50:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
---------------------------
-- 객체이름 : dbo.usp_CreatePlanet
-- 파라미터 : @pmPName NCHAR(10), @pmCName NCHAR(10)	, @pmPTheme INT, @pmPTerrain INT, @pmPObj INT
-- 제작자 : baboruri
-- 제작일 : 09-06-04
-- 변경일 : 
-- 내용 : 행성 생성
-- 결과
-- 성공 Return : 0;
-- PrimaryKey 중복 Return : 1
---------------------------
CREATE PROCEDURE [dbo].[usp_CreatePlanet]
	@pmPName		NCHAR(10),
	@pmCName		NCHAR(10),
	@pmPTheme		INT,
	@pmPTerrain	INT,
	@pmPObj		INT,
	@pmPTile			SMALLINT
AS
	SET NOCOUNT ON
	
	BEGIN TRY
		BEGIN TRAN	
			INSERT INTO PLANET_BASE( planetName, characterName )
			VALUES( @pmPName, @pmCName )				
		
		
			DECLARE @themeNum INT
			DECLARE @objInvenNum INT
			DECLARE @memo NCHAR(50) = RTRIM(@pmCName) + N'의 ' + RTRIM(@pmPName) + N' 행성 임!'

			EXECUTE WildPlanetDB.dbo.usp_InsertPlanetInven N'THEME',  @pmCName, @themeNum OUTPUT, @pmPTheme, 0, 1
			EXECUTE WildPlanetDB.dbo.usp_InsertPlanetInven N'OBJECT', @pmCName, @objInvenNum OUTPUT, @pmPObj, 0, 1

			INSERT INTO PLANET_CUSTOM( planetName, planetTheme, planetTerrain, planetMemo )
			VALUES( @pmPName, @themeNum, @pmPTerrain, @memo )
			
			INSERT INTO PLANET_OBJECT( planetName, objectNum, tileNum )
			VALUES( @pmPName, @objInvenNum, @pmPTile )
		COMMIT TRAN
		
		RETURN 0;
	END TRY
	
	BEGIN CATCH
	-- 이미 존재.
		ROLLBACK
		RETURN 1;
	END CATCH
GO
/****** Object:  StoredProcedure [dbo].[usp_CreateCharacter]    Script Date: 10/29/2018 19:50:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
---------------------------
-- 객체이름 : dbo.usp_CreateCharacter
-- 파라미터 : @pmName NCHAR(10), @pmId NCHAR(10), @pmType INT, @pmColor INT
-- 제작자 : baboruri
-- 제작일 : 09-06-01
-- 변경일 : 
-- 내용 : 케릭터 생성
-- 결과
-- 생생에 성공 Return : 0;
-- PrimaryKey 중복일 때 Return : 1
---------------------------
CREATE PROCEDURE [dbo].[usp_CreateCharacter]
	@pmName	NCHAR(10),
	@pmId		NCHAR(10),
	@pmType	INT,
	@pmColor	INT
AS
	SET NOCOUNT ON
	
	BEGIN TRY
		BEGIN TRAN	
			INSERT INTO CHARACTER_BASE( characterName, id, exper, gameMoney, starMoney, risingStar, birthday )
			VALUES( @pmName, @pmId, default, default, default, default, default )
								
			DECLARE @typeInvenNum INT
			DECLARE @colorInvenNum INT

			EXECUTE WildPlanetDB.dbo.usp_InsertAvatarInven N'TYPE',  @pmName, @typeInvenNum OUTPUT, @pmType, 0, 1
			EXECUTE WildPlanetDB.dbo.usp_InsertAvatarInven N'COLOR', @pmName, @colorInvenNum OUTPUT, @pmColor, 0, 1

			INSERT INTO CHARACTER_CUSTOM( characterName, characterType, characterColor )
			VALUES( @pmName, @typeInvenNum, @colorInvenNum )
		COMMIT TRAN		
		RETURN 0;
	END TRY
	
	BEGIN CATCH
	-- 이미 존재 또는 인벤이 비어서 실패야.
		ROLLBACK
		RETURN 1;
	END CATCH
GO
/****** Object:  StoredProcedure [dbo].[usp_BuyObject]    Script Date: 10/29/2018 19:50:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
---------------------------
-- 객체이름 : dbo.usp_BuyObject
-- 파라미터 : @pmName	NCHAR(10),	@pmItemCode	INT, @pmInvenNum	INT OUTPUT,	@pmGMoney	INT OUTPUT
-- 제작자 : baboruri
-- 제작일 : 09-06-11
-- 변경일 : 
-- 내용 : 행성 오브젝트 구입.
-- 결과
-- 성공 Return : 0;
-- 실패 Return : 1;
---------------------------
CREATE PROCEDURE [dbo].[usp_BuyObject]
	@pmName	NCHAR(10),
	@pmItemCode	INT,
	@pmInvenNum	INT OUTPUT,
	@pmSMoney	INT OUTPUT
AS
	SET NOCOUNT ON

	DECLARE @price INT
	DECLARE @category INT
	
	SELECT @category = objectCategory, @price = objectPrice
	FROM ITEM_OBJECT
	WHERE itemCode = @pmItemCode
	
	BEGIN TRY
		UPDATE CHARACTER_BASE
		SET @pmSMoney = starMoney -= @price
		WHERE characterName = @pmName
		
		IF( 30000 = @category )
			BEGIN
				EXECUTE WildPlanetDB.dbo.usp_InsertPlanetInven N'THEME', @pmName, @pmInvenNum OUTPUT, @pmItemCode, 1, 0
			END
		ELSE IF ( 10000 = @category )
			BEGIN
				EXECUTE WildPlanetDB.dbo.usp_InsertPlanetInven N'OBJECT', @pmName, @pmInvenNum OUTPUT, @pmItemCode, 1, 0
			END
		
		RETURN 0;
	END TRY
	BEGIN CATCH
		RETURN 1;
	END CATCH
GO
/****** Object:  StoredProcedure [dbo].[usp_BuyAvatar]    Script Date: 10/29/2018 19:50:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
---------------------------
-- 객체이름 : dbo.usp_BuyAvatar
-- 파라미터 : @pmName	NCHAR(10),	@pmItemCode	INT, @pmInvenNum	INT OUTPUT, @pmGMoney	INT OUTPUT
-- 제작자 : baboruri
-- 제작일 : 09-06-11
-- 변경일 : 
-- 내용 : 케릭터 아바타 구입.
-- 결과
-- 성공 Return : 0;
-- 실패 Return : 1;
---------------------------
CREATE PROCEDURE [dbo].[usp_BuyAvatar]
	@pmName	NCHAR(10),
	@pmItemCode	INT,
	@pmInvenNum	INT OUTPUT,
	@pmGMoney	INT OUTPUT
AS
	SET NOCOUNT ON

	DECLARE @price INT
	DECLARE @category INT
	
	SELECT @category = avatarCategory, @price = avatarPrice
	FROM ITEM_AVATAR
	WHERE itemCode = @pmItemCode
	
	BEGIN TRY
		UPDATE CHARACTER_BASE
		SET @pmGMoney = gameMoney -= @price
		WHERE characterName = @pmName
		
		IF( 40000 = @category )
			BEGIN
				EXECUTE WildPlanetDB.dbo.usp_InsertAvatarInven N'HEAD', @pmName, @pmInvenNum OUTPUT, @pmItemCode, 1, 0
			END
		ELSE IF ( 50000 = @category )
			BEGIN
				EXECUTE WildPlanetDB.dbo.usp_InsertAvatarInven N'COLOR', @pmName, @pmInvenNum OUTPUT, @pmItemCode, 1, 0
			END
		ELSE IF ( 60000 = @category )	
			BEGIN
				EXECUTE WildPlanetDB.dbo.usp_InsertAvatarInven N'BODY', @pmName, @pmInvenNum OUTPUT, @pmItemCode, 1, 0
			END
		ELSE IF ( 70000 = @category )
			BEGIN
				EXECUTE WildPlanetDB.dbo.usp_InsertAvatarInven N'TYPE', @pmName, @pmInvenNum OUTPUT, @pmItemCode, 1, 0
			END
	
		RETURN 0;
	END TRY
	BEGIN CATCH
		RETURN 1;
	END CATCH
GO
/****** Object:  Default [DF__ACCOUNT__account__72A6DC10]    Script Date: 10/29/2018 19:50:20 ******/
ALTER TABLE [dbo].[ACCOUNT] ADD  CONSTRAINT [DF__ACCOUNT__account__72A6DC10]  DEFAULT (getdate()) FOR [accountCreate]
GO
/****** Object:  Default [DF__CHARACTER__exper__758348BB]    Script Date: 10/29/2018 19:50:20 ******/
ALTER TABLE [dbo].[CHARACTER_BASE] ADD  DEFAULT ((0)) FOR [exper]
GO
/****** Object:  Default [DF__CHARACTER__gameM__76776CF4]    Script Date: 10/29/2018 19:50:20 ******/
ALTER TABLE [dbo].[CHARACTER_BASE] ADD  CONSTRAINT [DF__CHARACTER__gameM__76776CF4]  DEFAULT ((10000)) FOR [gameMoney]
GO
/****** Object:  Default [DF__CHARACTER__starM__785FB566]    Script Date: 10/29/2018 19:50:20 ******/
ALTER TABLE [dbo].[CHARACTER_BASE] ADD  CONSTRAINT [DF__CHARACTER__starM__785FB566]  DEFAULT ((100)) FOR [starMoney]
GO
/****** Object:  Default [DF__CHARACTER__risin__7A47FDD8]    Script Date: 10/29/2018 19:50:20 ******/
ALTER TABLE [dbo].[CHARACTER_BASE] ADD  CONSTRAINT [DF__CHARACTER__risin__7A47FDD8]  DEFAULT ((100)) FOR [risingStar]
GO
/****** Object:  Default [DF__CHARACTER__birth__7C30464A]    Script Date: 10/29/2018 19:50:20 ******/
ALTER TABLE [dbo].[CHARACTER_BASE] ADD  DEFAULT (getdate()) FOR [birthday]
GO
/****** Object:  Default [DF__TRADE_OBJ__buyTi__6CEE02BA]    Script Date: 10/29/2018 19:50:21 ******/
ALTER TABLE [dbo].[TRADE_OBJECT] ADD  DEFAULT (getdate()) FOR [buyTime]
GO
/****** Object:  Default [DF__TRADE_AVA__buyTi__68294D9D]    Script Date: 10/29/2018 19:50:21 ******/
ALTER TABLE [dbo].[TRADE_AVATAR] ADD  DEFAULT (getdate()) FOR [buyTime]
GO
/****** Object:  Default [DF__INVEN_TYP__itemU__03D16812]    Script Date: 10/29/2018 19:50:21 ******/
ALTER TABLE [dbo].[INVEN_TYPE] ADD  DEFAULT ((0)) FOR [itemUse]
GO
/****** Object:  Default [DF__INVEN_THE__itemU__1BA8F1A3]    Script Date: 10/29/2018 19:50:21 ******/
ALTER TABLE [dbo].[INVEN_THEME] ADD  DEFAULT ((0)) FOR [itemUse]
GO
/****** Object:  Default [DF__INVEN_OBJ__itemU__16E43C86]    Script Date: 10/29/2018 19:50:21 ******/
ALTER TABLE [dbo].[INVEN_OBJECT] ADD  DEFAULT ((0)) FOR [itemUse]
GO
/****** Object:  Default [DF__INVEN_HEA__itemU__0D5AD24C]    Script Date: 10/29/2018 19:50:21 ******/
ALTER TABLE [dbo].[INVEN_HEAD] ADD  DEFAULT ((0)) FOR [itemUse]
GO
/****** Object:  Default [DF__INVEN_COL__itemU__08961D2F]    Script Date: 10/29/2018 19:50:21 ******/
ALTER TABLE [dbo].[INVEN_COLOR] ADD  DEFAULT ((0)) FOR [itemUse]
GO
/****** Object:  Default [DF__INVEN_BOD__itemU__121F8769]    Script Date: 10/29/2018 19:50:21 ******/
ALTER TABLE [dbo].[INVEN_BODY] ADD  DEFAULT ((0)) FOR [itemUse]
GO
/****** Object:  Check [CK__CHARACTER__gameM__776B912D]    Script Date: 10/29/2018 19:50:20 ******/
ALTER TABLE [dbo].[CHARACTER_BASE]  WITH CHECK ADD CHECK  (([gameMoney]>=(0)))
GO
/****** Object:  Check [CK__CHARACTER__risin__7B3C2211]    Script Date: 10/29/2018 19:50:20 ******/
ALTER TABLE [dbo].[CHARACTER_BASE]  WITH CHECK ADD CHECK  (([risingStar]>=(0)))
GO
/****** Object:  Check [CK__CHARACTER__starM__7953D99F]    Script Date: 10/29/2018 19:50:20 ******/
ALTER TABLE [dbo].[CHARACTER_BASE]  WITH CHECK ADD CHECK  (([starMoney]>=(0)))
GO
/****** Object:  Check [CK__ITEM_AVAT__avata__5E9FE363]    Script Date: 10/29/2018 19:50:20 ******/
ALTER TABLE [dbo].[ITEM_AVATAR]  WITH CHECK ADD CHECK  (([avatarPrice]>=(0)))
GO
/****** Object:  Check [CK__ITEM_OBJE__objec__62707447]    Script Date: 10/29/2018 19:50:20 ******/
ALTER TABLE [dbo].[ITEM_OBJECT]  WITH CHECK ADD CHECK  (([objectPrice]>=(0)))
GO
/****** Object:  ForeignKey [FK__CHARACTER_BASE__ACCOUNT]    Script Date: 10/29/2018 19:50:20 ******/
ALTER TABLE [dbo].[CHARACTER_BASE]  WITH CHECK ADD  CONSTRAINT [FK__CHARACTER_BASE__ACCOUNT] FOREIGN KEY([id])
REFERENCES [dbo].[ACCOUNT] ([id])
ON UPDATE CASCADE
ON DELETE CASCADE
GO
ALTER TABLE [dbo].[CHARACTER_BASE] CHECK CONSTRAINT [FK__CHARACTER_BASE__ACCOUNT]
GO
/****** Object:  ForeignKey [FK__ITEM_AVATAR__ITEM_CATEGORY]    Script Date: 10/29/2018 19:50:20 ******/
ALTER TABLE [dbo].[ITEM_AVATAR]  WITH CHECK ADD  CONSTRAINT [FK__ITEM_AVATAR__ITEM_CATEGORY] FOREIGN KEY([avatarCategory])
REFERENCES [dbo].[ITEM_CATEGORY] ([categoryNum])
ON UPDATE CASCADE
ON DELETE CASCADE
GO
ALTER TABLE [dbo].[ITEM_AVATAR] CHECK CONSTRAINT [FK__ITEM_AVATAR__ITEM_CATEGORY]
GO
/****** Object:  ForeignKey [FK__ITEM_OBJECT__ITEM_CATEGORY]    Script Date: 10/29/2018 19:50:20 ******/
ALTER TABLE [dbo].[ITEM_OBJECT]  WITH CHECK ADD  CONSTRAINT [FK__ITEM_OBJECT__ITEM_CATEGORY] FOREIGN KEY([objectCategory])
REFERENCES [dbo].[ITEM_CATEGORY] ([categoryNum])
ON UPDATE CASCADE
ON DELETE CASCADE
GO
ALTER TABLE [dbo].[ITEM_OBJECT] CHECK CONSTRAINT [FK__ITEM_OBJECT__ITEM_CATEGORY]
GO
/****** Object:  ForeignKey [FK__PLANET_BASE__CHARACTER_BASE]    Script Date: 10/29/2018 19:50:21 ******/
ALTER TABLE [dbo].[PLANET_BASE]  WITH CHECK ADD  CONSTRAINT [FK__PLANET_BASE__CHARACTER_BASE] FOREIGN KEY([characterName])
REFERENCES [dbo].[CHARACTER_BASE] ([characterName])
ON UPDATE CASCADE
ON DELETE CASCADE
GO
ALTER TABLE [dbo].[PLANET_BASE] CHECK CONSTRAINT [FK__PLANET_BASE__CHARACTER_BASE]
GO
/****** Object:  ForeignKey [FK__TRADE_OBJECT__DEAL_MODE]    Script Date: 10/29/2018 19:50:21 ******/
ALTER TABLE [dbo].[TRADE_OBJECT]  WITH CHECK ADD  CONSTRAINT [FK__TRADE_OBJECT__DEAL_MODE] FOREIGN KEY([dealMode])
REFERENCES [dbo].[DEAL_MODE] ([dealMode])
ON UPDATE CASCADE
ON DELETE CASCADE
GO
ALTER TABLE [dbo].[TRADE_OBJECT] CHECK CONSTRAINT [FK__TRADE_OBJECT__DEAL_MODE]
GO
/****** Object:  ForeignKey [FK__TRADE_OBJECT__ITEM_OBJECT]    Script Date: 10/29/2018 19:50:21 ******/
ALTER TABLE [dbo].[TRADE_OBJECT]  WITH CHECK ADD  CONSTRAINT [FK__TRADE_OBJECT__ITEM_OBJECT] FOREIGN KEY([itemCode])
REFERENCES [dbo].[ITEM_OBJECT] ([itemCode])
ON UPDATE CASCADE
ON DELETE CASCADE
GO
ALTER TABLE [dbo].[TRADE_OBJECT] CHECK CONSTRAINT [FK__TRADE_OBJECT__ITEM_OBJECT]
GO
/****** Object:  ForeignKey [FK__TRADE_AVATAR__DEAL_MODE]    Script Date: 10/29/2018 19:50:21 ******/
ALTER TABLE [dbo].[TRADE_AVATAR]  WITH CHECK ADD  CONSTRAINT [FK__TRADE_AVATAR__DEAL_MODE] FOREIGN KEY([dealMode])
REFERENCES [dbo].[DEAL_MODE] ([dealMode])
ON UPDATE CASCADE
ON DELETE CASCADE
GO
ALTER TABLE [dbo].[TRADE_AVATAR] CHECK CONSTRAINT [FK__TRADE_AVATAR__DEAL_MODE]
GO
/****** Object:  ForeignKey [FK__TRADE_AVATAR__ITEM_AVATAR]    Script Date: 10/29/2018 19:50:21 ******/
ALTER TABLE [dbo].[TRADE_AVATAR]  WITH CHECK ADD  CONSTRAINT [FK__TRADE_AVATAR__ITEM_AVATAR] FOREIGN KEY([itemCode])
REFERENCES [dbo].[ITEM_AVATAR] ([itemCode])
ON UPDATE CASCADE
ON DELETE CASCADE
GO
ALTER TABLE [dbo].[TRADE_AVATAR] CHECK CONSTRAINT [FK__TRADE_AVATAR__ITEM_AVATAR]
GO
/****** Object:  ForeignKey [FK__INVEN_TYPE__CHARACTER_BASE]    Script Date: 10/29/2018 19:50:21 ******/
ALTER TABLE [dbo].[INVEN_TYPE]  WITH CHECK ADD  CONSTRAINT [FK__INVEN_TYPE__CHARACTER_BASE] FOREIGN KEY([characterName])
REFERENCES [dbo].[CHARACTER_BASE] ([characterName])
ON UPDATE CASCADE
ON DELETE CASCADE
GO
ALTER TABLE [dbo].[INVEN_TYPE] CHECK CONSTRAINT [FK__INVEN_TYPE__CHARACTER_BASE]
GO
/****** Object:  ForeignKey [FK__INVEN_TYPE__ITEM_AVATAR]    Script Date: 10/29/2018 19:50:21 ******/
ALTER TABLE [dbo].[INVEN_TYPE]  WITH CHECK ADD  CONSTRAINT [FK__INVEN_TYPE__ITEM_AVATAR] FOREIGN KEY([itemCode])
REFERENCES [dbo].[ITEM_AVATAR] ([itemCode])
ON UPDATE CASCADE
ON DELETE CASCADE
GO
ALTER TABLE [dbo].[INVEN_TYPE] CHECK CONSTRAINT [FK__INVEN_TYPE__ITEM_AVATAR]
GO
/****** Object:  ForeignKey [FK__INVEN_THEME__CHARACTER_BASE]    Script Date: 10/29/2018 19:50:21 ******/
ALTER TABLE [dbo].[INVEN_THEME]  WITH CHECK ADD  CONSTRAINT [FK__INVEN_THEME__CHARACTER_BASE] FOREIGN KEY([characterName])
REFERENCES [dbo].[CHARACTER_BASE] ([characterName])
ON UPDATE CASCADE
ON DELETE CASCADE
GO
ALTER TABLE [dbo].[INVEN_THEME] CHECK CONSTRAINT [FK__INVEN_THEME__CHARACTER_BASE]
GO
/****** Object:  ForeignKey [FK__INVEN_THEME__ITEM_OBJECT]    Script Date: 10/29/2018 19:50:21 ******/
ALTER TABLE [dbo].[INVEN_THEME]  WITH CHECK ADD  CONSTRAINT [FK__INVEN_THEME__ITEM_OBJECT] FOREIGN KEY([itemCode])
REFERENCES [dbo].[ITEM_OBJECT] ([itemCode])
ON UPDATE CASCADE
ON DELETE CASCADE
GO
ALTER TABLE [dbo].[INVEN_THEME] CHECK CONSTRAINT [FK__INVEN_THEME__ITEM_OBJECT]
GO
/****** Object:  ForeignKey [FK__INVEN_OBJECT__CHARACTER_BASE]    Script Date: 10/29/2018 19:50:21 ******/
ALTER TABLE [dbo].[INVEN_OBJECT]  WITH CHECK ADD  CONSTRAINT [FK__INVEN_OBJECT__CHARACTER_BASE] FOREIGN KEY([characterName])
REFERENCES [dbo].[CHARACTER_BASE] ([characterName])
ON UPDATE CASCADE
ON DELETE CASCADE
GO
ALTER TABLE [dbo].[INVEN_OBJECT] CHECK CONSTRAINT [FK__INVEN_OBJECT__CHARACTER_BASE]
GO
/****** Object:  ForeignKey [FK__INVEN_OBJECT__ITEM_OBJECT]    Script Date: 10/29/2018 19:50:21 ******/
ALTER TABLE [dbo].[INVEN_OBJECT]  WITH CHECK ADD  CONSTRAINT [FK__INVEN_OBJECT__ITEM_OBJECT] FOREIGN KEY([itemCode])
REFERENCES [dbo].[ITEM_OBJECT] ([itemCode])
ON UPDATE CASCADE
ON DELETE CASCADE
GO
ALTER TABLE [dbo].[INVEN_OBJECT] CHECK CONSTRAINT [FK__INVEN_OBJECT__ITEM_OBJECT]
GO
/****** Object:  ForeignKey [FK__INVEN_HEAD__CHARACTER_BASE]    Script Date: 10/29/2018 19:50:21 ******/
ALTER TABLE [dbo].[INVEN_HEAD]  WITH CHECK ADD  CONSTRAINT [FK__INVEN_HEAD__CHARACTER_BASE] FOREIGN KEY([characterName])
REFERENCES [dbo].[CHARACTER_BASE] ([characterName])
ON UPDATE CASCADE
ON DELETE CASCADE
GO
ALTER TABLE [dbo].[INVEN_HEAD] CHECK CONSTRAINT [FK__INVEN_HEAD__CHARACTER_BASE]
GO
/****** Object:  ForeignKey [FK__INVEN_HEAD__ITEM_AVATAR]    Script Date: 10/29/2018 19:50:21 ******/
ALTER TABLE [dbo].[INVEN_HEAD]  WITH CHECK ADD  CONSTRAINT [FK__INVEN_HEAD__ITEM_AVATAR] FOREIGN KEY([itemCode])
REFERENCES [dbo].[ITEM_AVATAR] ([itemCode])
ON UPDATE CASCADE
ON DELETE CASCADE
GO
ALTER TABLE [dbo].[INVEN_HEAD] CHECK CONSTRAINT [FK__INVEN_HEAD__ITEM_AVATAR]
GO
/****** Object:  ForeignKey [FK__INVEN_COLOR__CHARACTER_BASE]    Script Date: 10/29/2018 19:50:21 ******/
ALTER TABLE [dbo].[INVEN_COLOR]  WITH CHECK ADD  CONSTRAINT [FK__INVEN_COLOR__CHARACTER_BASE] FOREIGN KEY([characterName])
REFERENCES [dbo].[CHARACTER_BASE] ([characterName])
ON UPDATE CASCADE
ON DELETE CASCADE
GO
ALTER TABLE [dbo].[INVEN_COLOR] CHECK CONSTRAINT [FK__INVEN_COLOR__CHARACTER_BASE]
GO
/****** Object:  ForeignKey [FK__INVEN_COLOR__ITEM_AVATAR]    Script Date: 10/29/2018 19:50:21 ******/
ALTER TABLE [dbo].[INVEN_COLOR]  WITH CHECK ADD  CONSTRAINT [FK__INVEN_COLOR__ITEM_AVATAR] FOREIGN KEY([itemCode])
REFERENCES [dbo].[ITEM_AVATAR] ([itemCode])
ON UPDATE CASCADE
ON DELETE CASCADE
GO
ALTER TABLE [dbo].[INVEN_COLOR] CHECK CONSTRAINT [FK__INVEN_COLOR__ITEM_AVATAR]
GO
/****** Object:  ForeignKey [FK__INVEN_BODY__CHARACTER_BASE]    Script Date: 10/29/2018 19:50:21 ******/
ALTER TABLE [dbo].[INVEN_BODY]  WITH CHECK ADD  CONSTRAINT [FK__INVEN_BODY__CHARACTER_BASE] FOREIGN KEY([characterName])
REFERENCES [dbo].[CHARACTER_BASE] ([characterName])
ON UPDATE CASCADE
ON DELETE CASCADE
GO
ALTER TABLE [dbo].[INVEN_BODY] CHECK CONSTRAINT [FK__INVEN_BODY__CHARACTER_BASE]
GO
/****** Object:  ForeignKey [FK__INVEN_BODY__ITEM_AVATAR]    Script Date: 10/29/2018 19:50:21 ******/
ALTER TABLE [dbo].[INVEN_BODY]  WITH CHECK ADD  CONSTRAINT [FK__INVEN_BODY__ITEM_AVATAR] FOREIGN KEY([itemCode])
REFERENCES [dbo].[ITEM_AVATAR] ([itemCode])
ON UPDATE CASCADE
ON DELETE CASCADE
GO
ALTER TABLE [dbo].[INVEN_BODY] CHECK CONSTRAINT [FK__INVEN_BODY__ITEM_AVATAR]
GO
/****** Object:  ForeignKey [FK__FRIEND_LIST__CHARACTER_BASE]    Script Date: 10/29/2018 19:50:21 ******/
ALTER TABLE [dbo].[FRIEND_LIST]  WITH CHECK ADD  CONSTRAINT [FK__FRIEND_LIST__CHARACTER_BASE] FOREIGN KEY([characterName])
REFERENCES [dbo].[CHARACTER_BASE] ([characterName])
ON UPDATE CASCADE
ON DELETE CASCADE
GO
ALTER TABLE [dbo].[FRIEND_LIST] CHECK CONSTRAINT [FK__FRIEND_LIST__CHARACTER_BASE]
GO
/****** Object:  ForeignKey [FK__FRIEND_LIST1__CHARACTER_BASE]    Script Date: 10/29/2018 19:50:21 ******/
ALTER TABLE [dbo].[FRIEND_LIST]  WITH CHECK ADD  CONSTRAINT [FK__FRIEND_LIST1__CHARACTER_BASE] FOREIGN KEY([fName])
REFERENCES [dbo].[CHARACTER_BASE] ([characterName])
GO
ALTER TABLE [dbo].[FRIEND_LIST] CHECK CONSTRAINT [FK__FRIEND_LIST1__CHARACTER_BASE]
GO
/****** Object:  ForeignKey [FK__CHARACTER_CUSTOM__CHARACTER_BASE]    Script Date: 10/29/2018 19:50:21 ******/
ALTER TABLE [dbo].[CHARACTER_CUSTOM]  WITH CHECK ADD  CONSTRAINT [FK__CHARACTER_CUSTOM__CHARACTER_BASE] FOREIGN KEY([characterName])
REFERENCES [dbo].[CHARACTER_BASE] ([characterName])
ON UPDATE CASCADE
ON DELETE CASCADE
GO
ALTER TABLE [dbo].[CHARACTER_CUSTOM] CHECK CONSTRAINT [FK__CHARACTER_CUSTOM__CHARACTER_BASE]
GO
/****** Object:  ForeignKey [FK__CHARACTER_CUSTOM_BODY__INVEN_BODY]    Script Date: 10/29/2018 19:50:21 ******/
ALTER TABLE [dbo].[CHARACTER_CUSTOM]  WITH CHECK ADD  CONSTRAINT [FK__CHARACTER_CUSTOM_BODY__INVEN_BODY] FOREIGN KEY([characterBody])
REFERENCES [dbo].[INVEN_BODY] ([invenNum])
GO
ALTER TABLE [dbo].[CHARACTER_CUSTOM] CHECK CONSTRAINT [FK__CHARACTER_CUSTOM_BODY__INVEN_BODY]
GO
/****** Object:  ForeignKey [FK__CHARACTER_CUSTOM_COLOR__INVEN_COLOR]    Script Date: 10/29/2018 19:50:21 ******/
ALTER TABLE [dbo].[CHARACTER_CUSTOM]  WITH CHECK ADD  CONSTRAINT [FK__CHARACTER_CUSTOM_COLOR__INVEN_COLOR] FOREIGN KEY([characterColor])
REFERENCES [dbo].[INVEN_COLOR] ([invenNum])
GO
ALTER TABLE [dbo].[CHARACTER_CUSTOM] CHECK CONSTRAINT [FK__CHARACTER_CUSTOM_COLOR__INVEN_COLOR]
GO
/****** Object:  ForeignKey [FK__CHARACTER_CUSTOM_HEAD__INVEN_HEAD]    Script Date: 10/29/2018 19:50:21 ******/
ALTER TABLE [dbo].[CHARACTER_CUSTOM]  WITH CHECK ADD  CONSTRAINT [FK__CHARACTER_CUSTOM_HEAD__INVEN_HEAD] FOREIGN KEY([characterHead])
REFERENCES [dbo].[INVEN_HEAD] ([invenNum])
GO
ALTER TABLE [dbo].[CHARACTER_CUSTOM] CHECK CONSTRAINT [FK__CHARACTER_CUSTOM_HEAD__INVEN_HEAD]
GO
/****** Object:  ForeignKey [FK__CHARACTER_CUSTOM_TYPE__INVEN_TYPE]    Script Date: 10/29/2018 19:50:21 ******/
ALTER TABLE [dbo].[CHARACTER_CUSTOM]  WITH CHECK ADD  CONSTRAINT [FK__CHARACTER_CUSTOM_TYPE__INVEN_TYPE] FOREIGN KEY([characterType])
REFERENCES [dbo].[INVEN_TYPE] ([invenNum])
GO
ALTER TABLE [dbo].[CHARACTER_CUSTOM] CHECK CONSTRAINT [FK__CHARACTER_CUSTOM_TYPE__INVEN_TYPE]
GO
/****** Object:  ForeignKey [FK__PLANET_CUSTOM__INVEN_OBJECT]    Script Date: 10/29/2018 19:50:21 ******/
ALTER TABLE [dbo].[PLANET_OBJECT]  WITH CHECK ADD  CONSTRAINT [FK__PLANET_CUSTOM__INVEN_OBJECT] FOREIGN KEY([objectNum])
REFERENCES [dbo].[INVEN_OBJECT] ([invenNum])
GO
ALTER TABLE [dbo].[PLANET_OBJECT] CHECK CONSTRAINT [FK__PLANET_CUSTOM__INVEN_OBJECT]
GO
/****** Object:  ForeignKey [FK__PLANET_OBJECT__PLANET_BASE]    Script Date: 10/29/2018 19:50:21 ******/
ALTER TABLE [dbo].[PLANET_OBJECT]  WITH CHECK ADD  CONSTRAINT [FK__PLANET_OBJECT__PLANET_BASE] FOREIGN KEY([planetName])
REFERENCES [dbo].[PLANET_BASE] ([planetName])
ON UPDATE CASCADE
ON DELETE CASCADE
GO
ALTER TABLE [dbo].[PLANET_OBJECT] CHECK CONSTRAINT [FK__PLANET_OBJECT__PLANET_BASE]
GO
/****** Object:  ForeignKey [FK__PLANET_CUSTOM__INVEN_THEME]    Script Date: 10/29/2018 19:50:21 ******/
ALTER TABLE [dbo].[PLANET_CUSTOM]  WITH CHECK ADD  CONSTRAINT [FK__PLANET_CUSTOM__INVEN_THEME] FOREIGN KEY([planetTheme])
REFERENCES [dbo].[INVEN_THEME] ([invenNum])
GO
ALTER TABLE [dbo].[PLANET_CUSTOM] CHECK CONSTRAINT [FK__PLANET_CUSTOM__INVEN_THEME]
GO
/****** Object:  ForeignKey [FK__PLANET_CUSTOM__ITEM_OBJECT]    Script Date: 10/29/2018 19:50:21 ******/
ALTER TABLE [dbo].[PLANET_CUSTOM]  WITH CHECK ADD  CONSTRAINT [FK__PLANET_CUSTOM__ITEM_OBJECT] FOREIGN KEY([planetTerrain])
REFERENCES [dbo].[ITEM_OBJECT] ([itemCode])
GO
ALTER TABLE [dbo].[PLANET_CUSTOM] CHECK CONSTRAINT [FK__PLANET_CUSTOM__ITEM_OBJECT]
GO
/****** Object:  ForeignKey [FK__PLANET_CUSTOM__PLANET_BASE]    Script Date: 10/29/2018 19:50:21 ******/
ALTER TABLE [dbo].[PLANET_CUSTOM]  WITH CHECK ADD  CONSTRAINT [FK__PLANET_CUSTOM__PLANET_BASE] FOREIGN KEY([planetName])
REFERENCES [dbo].[PLANET_BASE] ([planetName])
ON UPDATE CASCADE
ON DELETE CASCADE
GO
ALTER TABLE [dbo].[PLANET_CUSTOM] CHECK CONSTRAINT [FK__PLANET_CUSTOM__PLANET_BASE]
GO
