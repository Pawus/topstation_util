/* Version 0.2                                                            */
/*  derni�re modification :                                               */
/*         16 09 2013 (SD)                                                */
/*  auteur :                                                              */
/*         SD Samuel D�om (sdeom@epadesa.fr)                              */

/* Cette boite � outils contient des routines permettant le traitement    */
/*  des param�tres de projection, notamment en lien avec la norme EPSG    */

/* Pour fonctionner il faut inclure pr�alablement les boites � outils     */
/*  epListeOutils                                                         */
/*  epTexteOutils                                                         */
/*  epNumOutils                                                           */
/*  epRalOutils                                                           */

/* Liste des routines                                                     */
/*  DetEllips(�prc_txt) D�termine le nom usuel de l'ellipsoide de la base */
/*         en cours                                                       */
/*         derni�re modification : 16 09 2013 (SD)                        */
/*  DetSysG(�prc_txt) D�termine le nom du syst�me g�od�sique suppos� de   */
/*         de la base en cours, en se basant sur des extrapolation �      */
/*         partir de l'ellipsoide                                         */
/*         derni�re modification : 16 09 2013 (SD)                        */
/*  SPJversSRID(�spj,�nom_prc) Renvoie le SRID d'une projection           */
/*         indentifi�e � partir de son abr�viation TopoStation            */
/*         derni�re modification : 16 09 2013 (SD)                        */
/*  SRIDbase(�nom_prc) Renvoie le SRID de la base active                  */
/*         derni�re modification : 16 09 2013 (SD)                        */
/*  ValidSrid(�srid,�prc_ok) Verifie que la valeur                        */
/*         derni�re modification : 16 09 2013 (SD)                        */

rout,DetEllips(�prc_txt)
/* Enregistre dans la proc�dure dont le nom est pass� dans �prc_txt le    */
/*  nom usuel de l'ellipsoide de la base en cours                         */
{
  if,"[%SPJ:AE==6378137.0]#[%SPJ:BE==6356752.3141]"
  then
  {
    [�prc_txt]="GRS 1980"
  }
  else
  {
    if,"[%SPJ:AE==6378249.2]#[%SPJ:BE==6356515.0]"
    then
    {
      [�prc_txt]="Clarke 1880 version IGN"
    }
    else
    {
      if,"[%SPJ:AE==6378388]#[%SPJ:BE==6356911.94612795]"
      then
      {
        [�prc_txt]="Hayford 1909"
      }
      else
      {
        [�prc_txt]="Indetermin�"
      }
    }
  }
}

rout,DetSysG(�prc_txt)
/* Enregistre dans la proc�dure dont le nom est pass� dans �prc_txt le    */
/*  nom du syst�me g�od�sique suppos� de la base en cours, en se basant   */
/*  sur des extrapolation � partir de l'ellipsoide                        */
{
if,"[%SPJ:AE==6378137.0]#[%SPJ:BE==6356752.3141]"
  then
  {
    [�prc_txt]="RGF 93"
  }
  else
  {
    if,"[%SPJ:AE==6378249.2]#[%SPJ:BE==6356515.0]"
    then
    {
      [�prc_txt]="NTF"
    }
    else
    {
      if,"[%SPJ:AE==6378388]#[%SPJ:BE==6356911.94612795]"
      then
      {
        [�prc_txt]="ED50"
      }
      else
      {
        [�prc_txt]="Indetermin�"
      }
    }
  }
}

rout,SPJversSRID(�spj,�nom_prc)
/* Permet d'instancier la proc�dure dont le nom est contenu dans �nom_prc */
/*  avec la valeur de l'identifiant de l'indicateurs de r�f�rence         */
/*  (spatiale SRID) � la norme EPSG correspondant au syst�me de           */
/*  projection dont l'abr�viation (pseudo-param�tre ZONE)                 */
/*  contenu dans �spj                                                     */
/* Pour les syst�mes maintenus par l'IGN, les srid correpondent � ceux    */
/*  que celui-ci fourni, cf fichier : "IGNF-spatial_ref_sys.sql"          */
/* Un syst�me local ou inconnu est repr�sent� par la valeur 0             */
{
  var,�srid,�i
  
  �srid=0
  
  /* cas du Lambert93 (RGF93) */
  if,"�spj==`L93`" 
  {
    �srid=IGNF::310024140
  }
  
  /* cas des CC42 � CC50 (RGF93) */
  for,"42->�i","�i<51","�i+1->�i"
  {
    if,"�spj==`L[�i]`" 
    {
      �srid=IGNF::3100241[�i]
    }
  }
  
  /* cas du Lambert I France Nord (NTF) */
  if,"�spj==`LFN`" 
  {
    �srid=IGNF::320002101
  }
  
  [�nom_prc]=[�srid]
}


rout,SRIDbase(�nom_prc)
/* Permet d'instancier la proc�dure dont le nom est contenu dans �nom_prc */
/*  avec la valeur de l'identifiant de l'indicateurs de r�f�rence         */
/*  (spatiale SRID) � la norme EPSG correspondant au syst�me de           */
/*  projection de la base en cours                                        */
/* Voir SPJversSRID pour le de�tail sur les valeurs de sortie             */
{
  run,SPJversSRID([%SPJ:ZONE],[�nom_prc])
}

rout,CheckSrid(�prc_srid,�prc_ok)
/* Enregistre dans la proc�dure dont le nom est pass� dans �prc_txt le    */
/*  nom usuel de l'ellipsoide de la base en cours                         */
{
  var,�ok,�spj,�par
  �ok=0
  run,FormateTexte(%SPJ:ZONE,�par)
  
  if,"%SPJ:TY==0" 
  then
  {
    �ok=1
  }
  else
  {
    run,VtoQ([�prc_srid],�spj,sridZone)
	if,"�spj==�par"
	{
	  �ok=1
	}
  }
  
  [�prc_ok]=[�ok]
}