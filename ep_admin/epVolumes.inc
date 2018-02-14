/* version 0.1 du                                                         */
/*  dernière modification :                                               */
/*         22 02 2013 (SD)                                                */
/*  auteur :                                                              */
/*         SD Samuel Déom (sdeom@epadesa.fr)                              */

/* Pour fonctionner il faut inclure préalablement les boites à outils :   */
/*  epRamses                                                              */
/*  epRalOutils                                                           */

rout,ImpFid(§prc_sel)
{
  var,§fid,§ma
  
  runs,[[§prc_sel]]
  {
    §ma=[mm]
	if,"[[§ma]&r0:e]&v57:vid><``"
	{
	  |  SELECT [SchemaRf].[TblVol].fid AS "§fid:PRC"
      |    FROM [SchemaRf].[TblVol]
      |    WHERE [SchemaRf].[TblVol].vid = [[[§ma]&r0:e]&v57:vid]
	  |      AND [SchemaRf].[TblVol].numero = [[§ma]&t2:nom];
	  
	  ral,[§ma]&v57:fid=[§fid]
	}
  }
}

rout,ImpDataFED(§prc_sel)
{
  var,§ma
  var,§nom,§nedd
  
  runs,[[§prc_sel]]
  {
    §ma=[mm]
	if,"[§ma]&v57:vid><``"
	{
	  |  SELECT [SchemaRf].[TblEddv].nom AS "§nom:PRC"
	  |      , [SchemaRf].[TblEddv].nodossier AS "§nedd:PRC"
      |    FROM [SchemaRf].[TblEddv]
      |    WHERE [SchemaRf].[TblEddv].vid = [[§ma]&v57:vid];
	  
	  run,EcritRal(§nom,[§ma],Q1,nom,txt)
	  run,EcritRal(§nedd,[§ma],Q1,nedd,entier)
	}
  }
}

rout,ImpDataFLD(§prc_sel)
{
  var,§sec,§com,§pre,§num
  var,§nom_com,§nom_dep
  var,§cpt
  
  runs,[[§prc_sel]]
  {
    |  SELECT [SchemaRf].[TblPrcl].sectionref AS "§sec:PRC"
	|      , [SchemaRf].[TblPrcl].codecommune AS "§com:PRC"
	|      , [SchemaRf].[TblPrcl].pre AS "§pre:PRC"
	|      , [SchemaRf].[TblPrcl].numero AS "§num:PRC"
    |    FROM [SchemaRf].[TblPrcl]
    |    WHERE [SchemaRf].[TblPrcl].fid = [[mm]&v57:fid];
    
    ral,[mm]&v1:sec="[§sec]",com=[[§com])03],pre="[§pre]",num=[§num],dep=92
	
	|  SELECT [SchemaRf].[TblFonds].pddpid AS "§cpt:PRC"
    |    FROM [SchemaRf].[TblFonds]
    |    WHERE [SchemaRf].[TblFonds].fid = [[mm]&v57:fid];
	
	ral,[mm]&v0:cpt="******+[[§cpt])05]"
  }
}
