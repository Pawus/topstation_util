/* version 0.2 du                                                         */
/*  dernière modification :                                               */
/*         10 04 2015 (SD)                                                */
/*  auteur :                                                              */
/*         SD Samuel Déom (sdeom@epadesa.fr)                              */

/* Pour fonctionner il faut inclure préalablement les boites à outils :   */
/*  epPlanOutils                                                          */

/* Liste des routines                                                     */
/*  CreePlan(§fed) Créer un plan nouveau lié à la volumétrie §fed         */
/*		Dernière modification : 10/04/2015								  */
/*  SetRalE(§fed) Relie l'ensemble des */
/*		Dernière modification : 06/03/2013								  */

rout,CreePlanFed(§fed,§z,§nom_niv,§cx,§cy,§x,§y,§g,§ec,§mdl,§prc_cmp)
{
  var,§cmp,§dom,§nom,§num,§ind,§sufix
  var,§fedpro
  var,§z_txt,§niv_txt
  
  §cmp=[ml(`jtPlan`)]
  
  if,"[§z>900]#[§z<-900]"
  {
    §z_txt=
  }
  else
  {
    §z_txt= [§z%0]m
  }
  if,"§nom_niv==``"
  {
    §niv_txt=
  }
  else
  {
    §niv_txt= ([§nom_niv])
  }
  
  if,"[§fed]&Q4:etat==`PROJET`"
  {
    runs,Fedpro*!onc([§fed])
    {
      §num=[:i]
    }
	§ind=[upcn([§fed]&Q4:ind)]
	§sufix=>[§num][§ind]
  }
  else
  {
    §sufix=
  }
  §nom=F > [[§fed]&Q1:nab][§z_txt][§niv_txt][§sufix]
  
  [§cmp]:X=[§x],Y=[§y],Z=[§z],G=[§g],Cx=[§cx],Cy=[§cy]
  [§cmp]:PV=1,MD=[§mdl]
  [§cmp]&V0:Nom=[§nom],Ec=[§ec]
  [§cmp]&R0:E=[§fed]
  
  /* on définit le domaine du plan */
  if,"§sufix><``"
  {
	§sufix=_[§num][§ind]
  }
  §dom=JTPLAN[upcn([§cmp]:i)][§sufix]
  [§cmp]&D0:[§dom]
  
  /* on ajoute les instructions qui seront exécutées à l'affichage du plan */
  [§cmp]&K0:gom,!tout
  [§cmp]&K1:%DOM:DOM="[§dom]"
  [§cmp]&K2:tra,!dom([§dom])
  
  /* on ajoute l'eddv dans le domaine du plan */
  domi,[§dom],[§fed]  
  
  [§prc_cmp]=[§cmp]
}

rout,SetRalE(§fed)
{
  runs,!lini([§fed],-0.01)*[hbcFCL]
  {
    if,"[mm]&r0:e><`[hbcFED].%`"
    then
    {
      ral,[mm]&r0:e=[§fed]
    }
  }
  runs,!zoni([§fed],-0.01)*[hbcFCD]
  {
    if,"[mm]&r0:l><`[hbcFLD].%`"
    then
    {
      ral,[mm]&r0:e=[§fed]
    }
    else
    {
      if,"[[mm]&r0:l]&r0:e><`[hbcFED].%`"
      then
      {
        ral,[mm]&r0:e=[§fed]
        ral,[[mm]&r0:l]&r0:e=[§fed]
      }
      else
      {
        ral,[mm]&r0:e=[[[mm]&r0:l]&r0:e]
      }
    }
  }
}