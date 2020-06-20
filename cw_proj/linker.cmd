#
#	linker.cmd
#
#	CodeWarrior for Dreamcast standard linker command file
#	Version.1.0b2
#
#	Metrowerks inc
#
#       1999.03.15	for 1.0
#	1999.01.21	for beta 1.5
#	1998.11.25	for beta 1
#

$INCLUDE
{
	#	These sections have to be included in an execute file.
	IP
	DSGLH
	DSGLE

	#	This section have to be included for SOFDEC.lib.
	#	PSGSFD01

	#	don't dead strip .data section
	#.data
}

$SEGMENT CODE_SG_IP 0x8C008000 R
{
	*(IP)
}

$SEGMENT DATA_SG_LH 0x8C010000 R
{
	__START_DSGLH	= .;
	*(DSGLH) 
	__END_DSGLH		= .;
	
	__START_DSGLE	= .;
	*(DSGLE) 
	__END_DSGLE 	= .;
}

$SEGMENT CODE_USER R
{
	*(.text)
	*(P)
}

$SEGMENT CONST_USER R
{
	ALIGN(0x8)
	*(.rodata)
	ALIGN(0x8)
	*(C)
	*(C32)
}

$SEGMENT DATA_USER
{
	__START_D		= .;
	ALIGN(0x8)
	*(.data)
	ALIGN(0x8)
	*(D)
	__END_D 		= .;

	__START_D32		= .;
	*(D32)
	__END_D32		= .;

	#	these symbols are required for link
	__START_R		= .;
	__END_R			= .;
	__START_R32		= .;
	__END_R32		= .;
	#
}

$SEGMENT CODE_SG R
{
	*(PSG)
}

$SEGMENT CONST_SG R
{
	ALIGN(0x8)
	*(CSG)
	*(CSG32)
}

$SEGMENT DATA_SG
{
	__START_DSG		= .;
	ALIGN(0x8)
	*(DSG)
	__END_DSG		= .;

	__START_DSG32	= .;
	*(DSG32)
	__END_DSG32		= .;

	#	these symbols are required for link
	__START_RSG		= .;
	__END_RSG		= .;
	__START_RSG32	= .;
	__END_RSG32		= .;
	#
}

#	Ninja sections
#
#	$SEGMENT CODE_SG_NINJA R
#	{
#		PSGNJ00
#		PSGNJ01
#		PSGNJ02
#		PSGNJ03
#		PSGNJ04
#		PSGNJ05
#		PSGNJ06
#		PSGNJ07
#		PSGNJ08
#		PSGNJ09
#		PSGNJ10
#		PSGNJ11
#		PSGNJ12
#		PSGNJ13
#		PSGNJ14
#		PSGNJ15
#	}
#
#	$SEGMENT DATA_SG_NINJA
#	{
#		DSGNJ00
#		DSGNJ01
#		DSGNJ02
#		DSGNJ03
#		DSGNJ04
#		DSGNJ05
#		DSGNJ06
#		DSGNJ07
#		DSGNJ08
#		DSGNJ09
#		DSGNJ10
#		DSGNJ11
#		DSGNJ12
#		DSGNJ13
#		DSGNJ14
#		DSGNJ15
#	}

#	Middleware sections
#
#	$SEGMENT CODE_SG_MW R
#	{
#		PSGMW00
#		PSGMW01
#		PSGMW02
#		PSGMW03
#		PSGMW04
#		PSGMW05
#		PSGMW06
#		PSGMW07
#		PSGMW08
#		PSGMW09
#		PSGMW10
#		PSGMW11
#		PSGMW12
#		PSGMW13
#		PSGMW14
#		PSGMW15
#	}
#
#	$SEGMENT DATA_SG_MW
#	{
#		DSGMW00
#		DSGMW01
#		DSGMW02
#		DSGMW03
#		DSGMW04
#		DSGMW05
#		DSGMW06
#		DSGMW07
#		DSGMW08
#		DSGMW09
#		DSGMW10
#		DSGMW11
#		DSGMW12
#		DSGMW13
#		DSGMW14
#		DSGMW15
#	}

#	Sofdec sections
#
#	*** if you use SOFDEC.LIB, please remove "#" below. ***
#
#	$SEGMENT CODE_SG_SOFDEC R
#	{
#		__START_PSGSFD00	= .;
#		PSGSFD00
#		__END_PSGSFD00		= .;
#	
#		__START_PSGSFD01	= .;
#		PSGSFD01
#		__END_PSGSFD01		= .;
#	
#		__START_PSGSFD02	= .;
#		PSGSFD02
#		__END_PSGSFD02		= .;
#	
#		__START_PSGSFD03	= .;
#		PSGSFD03
#		__END_PSGSFD03		= .;
#	
#		__SIZE_PSGSFD00		= __END_PSGSFD00 - __START_PSGSFD00;
#		__SIZE_PSGSFD01		= __END_PSGSFD01 - __START_PSGSFD01;
#		__SIZE_PSGSFD02		= __END_PSGSFD02 - __START_PSGSFD02;
#		__SIZE_PSGSFD03		= __END_PSGSFD03 - __START_PSGSFD03;
#	}
#
#	$SEGMENT DATA_SG_SOFDEC
#	{
#		DSGSFD00
#		DSGSFD01
#		DSGSFD02
#		DSGSFD03
#	}

#	Reserved sections
#
#	$SEGMENT CODE_SG_RESERVED R
#	{
#		PSGRSV0
#		PSGRSV1
#		PSGRSV2
#		PSGRSV3
#	}
#
#	$SEGMENT DATA_SG_RESERVED
#	{
#		DSGRSV0
#		DSGRSV1
#		DSGRSV2
#		DSGRSV3
#	}

#	User Reserved sections
#
#	$SEGMENT CODE_USER_RESERVED R
#	{
#		PUSER0
#		PUSER1
#		PUSER2
#		PUSER3
#	}
#
#	$SEGMENT DATA_USER_RESERVED
#	{
#		DUSER0
#		DUSER1
#		DUSER2
#		DUSER3
#	}

$SEGMENT BSS_USER
{
	__START_B 		= .;
	ALIGN(0x8)
	*(.bss)
	ALIGN(0x8)
	*(B)
	__END_B			= .;

	__START_B32		= .;
	*(B32)
	__END_B32		= .;
}

$SEGMENT BSS_SG
{
	__START_BSG		= .;
	ALIGN(0x8)
	*(BSG)
	__END_BSG		= .;

	__START_BSG32	= .; 
	*(BSG32)
	__END_BSG32		= .;
}
