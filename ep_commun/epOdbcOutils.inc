/* version 0.1 du                                                         */
/*  derni�re modification :                                               */
/*         27 11 2012 (SD)                                                */
/*  auteur :                                                              */
/*         SD Samuel D�om (sdeom@epadesa.fr)                              */

/* N�cessite la biblioth�que iconv permettant de modifier l'encodage des  */
/*  de chaines de carat�res disponible sous license LGPL et GPL           */
/*  requiert iconv de gettext disponible � l'adresse :                    */
/*       http://gnuwin32.sourceforge.net/packages/gettext.htm             */
/*       http://www.gnu.org/software/libiconv/                            */
proc,EpGnu={util}\ep_commun\gnu
proc,EpIconvExe={EpGnu}\bin\iconv.exe /* localistation de l'exe iconv     */

/* Liste des routines                                                     */
/*  CreeDataSrc(�nom,�pilote,�serveur,�port,�base,�user,�pwd,�ssl)        */
/*         cr�� une source de donn�es ODBC                                */
/*         derni�re modification : 27 11 2012 (SD)                        */

proc,JtDebug=1

rout,CreeDataSrc(�nom,�pilote,�serveur,�port,�base,�user,�pwd,�ssl)
/* Fonction permettant de cr�er une source de donn�es MicroSoft ODBC      */
{
  var,�regfile,�iconv,�commande,�iconvBatch
  
  �regfile={base}\temp /* fichier temporaire d'�change avec la base de registre */
  �iconv={EpIconvExe} /* localistation de l'executable iconv */
  �iconvBatch={EpGnu}\batch\iconv_ucs-2le_cp850.bat
  
  if,"nlfic(�iconv)=-1"
  {
	impr,Erreur : inconv.exe manquant
	halt
  }
  if,"nlfic(�iconvBatch)=-1"
  {
	impr,Erreur : Fichier batch "iconv" manquant
	halt
  }
  
  /* Verification de l'existance du pilote */
  dos,`reg export "HKEY_LOCAL_MACHINE\SOFTWARE\ODBC\ODBCINST.INI\{�pilote}" "{�regfile}.reg"`
  
  �commande={�iconvBatch} {�iconv} "{�regfile}.reg" "{�regfile}.txt"
  list,{base}\list.txt
  impq,`{�commande}`
  dos,�commande
  list
  /* dos,`del "{�regfile}.reg"` */
  
  /* Creation de la source dans la liste des sources */
  /* dos,`reg add "HKEY_CURRENT_USER\Software\ODBC\ODBC.INI\ODBC Data Sources" /v [�nom] /t REG_SZ /d [�pilote]` */
  
  /* Creation de la source proprement dite */
  /* dos,`reg add "HKEY_CURRENT_USER\Software\ODBC\ODBC.INI\[�nom]" /v CommLog  /t REG_SZ /d 0` */
}

rout,Test
{
  var,�pilote,�regfile
  �pilote=PostGreSQL ANSI
  �regfile={base}\temp.txt
  
  dos,`reg query "HKEY_LOCAL_MACHINE\SOFTWARE\ODBC\ODBCINST.INI\{�pilote}"`,{base}\temp.txt
}

rout,CreeDataSrc2(�nom,�pilote,�serveur,�port,�base,�user,�pwd,�ssl,�description)
{
  /* Execution Batch */
  dos,`{epUtil}\batch\creepsql.bat {�nom} {�pilote}`
  /* {�serveur} {�port} {�base} {�user} {�pwd} {�ssl} {�description} */
}

rout,CreeDataSrc3
{
  var,�commande

  /* Execution Batch */
  �commande={epUtil}\batch\ex_cree.bat
  [ep]syst,�commande
}