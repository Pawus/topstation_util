/* version 0.1 du                                                         */
/*  dernière modification :                                               */
/*         22 02 2013 (SD)                                                */
/*  auteur :                                                              */
/*         SD Samuel Déom (sdeom@epadesa.fr)                              */

/* Pour fonctionner il faut inclure préalablement les boites à outils :   */
/*  epRamses                                                              */

rout,ImpFidFpar(§prc_sel)
{
  var,§fid
  
  runs,[[§prc_sel]]
  {
    |  SELECT [SchemaRf].[TblPrcl].fid AS "§fid:PRC"
    |   FROM [SchemaRf].[TblPrcl]
    |   WHERE [SchemaRf].[TblPrcl].codecommune = [[mm]&v1:com]
    |     AND [SchemaRf].[TblPrcl].sectionref = '[[mm]&v1:sec]'
    |     AND [SchemaRf].[TblPrcl].pre = '[[mm]&v1:pre]'
    |     AND [SchemaRf].[TblPrcl].numero = [[mm]&v1:num];
    
    ral,[mm]&v57:fid=[§fid]
  }
}

rout,ImpDataFpar(§prc_sel)
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
