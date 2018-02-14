/* Version 0.2                                                            */
/*  dernière modification :                                               */
/*         16 09 2013 (SD)                                                */
/*  auteur :                                                              */
/*         SD Samuel Déom (sdeom@epadesa.fr)                              */

/* Cette boite à outils contient des routines permettant le traitement    */
/*  des paramètres de projection, notamment en lien avec la norme EPSG    */

/* Pour fonctionner il faut inclure préalablement les boites à outils     */
/*  epListeOutils                                                         */
/*  epTexteOutils                                                         */
/*  epNumOutils                                                           */
/*  epRalOutils                                                           */

/* Liste des routines                                                     */
/*  DetEllips(§prc_txt) Détermine le nom usuel de l'ellipsoide de la base */
/*         en cours                                                       */
/*         dernière modification : 16 09 2013 (SD)                        */
/*  DetSysG(§prc_txt) Détermine le nom du système géodésique supposé de   */
/*         de la base en cours, en se basant sur des extrapolation à      */
/*         partir de l'ellipsoide                                         */
/*         dernière modification : 16 09 2013 (SD)                        */
/*  SPJversSRID(§spj,§nom_prc) Renvoie le SRID d'une projection           */
/*         indentifiée à partir de son abréviation TopoStation            */
/*         dernière modification : 16 09 2013 (SD)                        */
/*  SRIDbase(§nom_prc) Renvoie le SRID de la base active                  */
/*         dernière modification : 16 09 2013 (SD)                        */
/*  ValidSrid(§srid,§prc_ok) Verifie que la valeur                        */
/*         dernière modification : 16 09 2013 (SD)                        */

rout,DetEllips(§prc_txt)
/* Enregistre dans la procédure dont le nom est passé dans §prc_txt le    */
/*  nom usuel de l'ellipsoide de la base en cours                         */
{
  if,"[%SPJ:AE==6378137.0]#[%SPJ:BE==6356752.3141]"
  then
  {
    [§prc_txt]="GRS 1980"
  }
  else
  {
    if,"[%SPJ:AE==6378249.2]#[%SPJ:BE==6356515.0]"
    then
    {
      [§prc_txt]="Clarke 1880 version IGN"
    }
    else
    {
      if,"[%SPJ:AE==6378388]#[%SPJ:BE==6356911.94612795]"
      then
      {
        [§prc_txt]="Hayford 1909"
      }
      else
      {
        [§prc_txt]="Indeterminé"
      }
    }
  }
}

rout,DetSysG(§prc_txt)
/* Enregistre dans la procédure dont le nom est passé dans §prc_txt le    */
/*  nom du système géodésique supposé de la base en cours, en se basant   */
/*  sur des extrapolation à partir de l'ellipsoide                        */
{
if,"[%SPJ:AE==6378137.0]#[%SPJ:BE==6356752.3141]"
  then
  {
    [§prc_txt]="RGF 93"
  }
  else
  {
    if,"[%SPJ:AE==6378249.2]#[%SPJ:BE==6356515.0]"
    then
    {
      [§prc_txt]="NTF"
    }
    else
    {
      if,"[%SPJ:AE==6378388]#[%SPJ:BE==6356911.94612795]"
      then
      {
        [§prc_txt]="ED50"
      }
      else
      {
        [§prc_txt]="Indeterminé"
      }
    }
  }
}

rout,SPJversSRID(§spj,§nom_prc)
/* Permet d'instancier la procédure dont le nom est contenu dans §nom_prc */
/*  avec la valeur de l'identifiant de l'indicateurs de référence         */
/*  (spatiale SRID) à la norme EPSG correspondant au système de           */
/*  projection dont l'abréviation (pseudo-paramètre ZONE)                 */
/*  contenu dans §spj                                                     */
/* Pour les systèmes maintenus par l'IGN, les srid correpondent à ceux    */
/*  que celui-ci fourni, cf fichier : "IGNF-spatial_ref_sys.sql"          */
/* Un système local ou inconnu est représenté par la valeur 0             */
{
  var,§srid,§i
  
  §srid=0
  
  /* cas du Lambert93 (RGF93) */
  if,"§spj==`L93`" 
  {
    §srid=IGNF::310024140
  }
  
  /* cas des CC42 à CC50 (RGF93) */
  for,"42->§i","§i<51","§i+1->§i"
  {
    if,"§spj==`L[§i]`" 
    {
      §srid=IGNF::3100241[§i]
    }
  }
  
  /* cas du Lambert I France Nord (NTF) */
  if,"§spj==`LFN`" 
  {
    §srid=IGNF::320002101
  }
  
  [§nom_prc]=[§srid]
}


rout,SRIDbase(§nom_prc)
/* Permet d'instancier la procédure dont le nom est contenu dans §nom_prc */
/*  avec la valeur de l'identifiant de l'indicateurs de référence         */
/*  (spatiale SRID) à la norme EPSG correspondant au système de           */
/*  projection de la base en cours                                        */
/* Voir SPJversSRID pour le deétail sur les valeurs de sortie             */
{
  run,SPJversSRID([%SPJ:ZONE],[§nom_prc])
}

rout,CheckSrid(§prc_srid,§prc_ok)
/* Enregistre dans la procédure dont le nom est passé dans §prc_txt le    */
/*  nom usuel de l'ellipsoide de la base en cours                         */
{
  var,§ok,§spj,§par
  §ok=0
  run,FormateTexte(%SPJ:ZONE,§par)
  
  if,"%SPJ:TY==0" 
  then
  {
    §ok=1
  }
  else
  {
    run,VtoQ([§prc_srid],§spj,sridZone)
	if,"§spj==§par"
	{
	  §ok=1
	}
  }
  
  [§prc_ok]=[§ok]
}