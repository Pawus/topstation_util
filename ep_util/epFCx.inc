/* version 0.1 du                                                           */
/*  dernière modification :                                                 */
/*         19 15 2015 (SD)                                                  */
/*  auteur :                                                                */
/*         SD Samuel Déom (sdeom@epadesa.fr)                                */

/* Pour fonctionner il faut inclure préalablement les boites à outils :     */
/*   epDateOutils                                                           */
/*   epRalOutils                                                            */
/*   epCmpOutils                                                            */
/*   epTypeOutils (pour epRalOutils)                                        */
/*   epTexteOutils (pour epRalOutils)                                       */
/*   epNumOutils   (pour epRalOutils)                                       */

/*--------------------------------------------------------------------------*/
/*                                PROCEDURES                                */
/*                         par ordre alphabétique                           */
/*--------------------------------------------------------------------------*/
/* modèle par défaut pour les limites de coupes de volumes */
proc,Fcl_md=EP_LIN_VOLUME 
/* type par défaut pour les limites de coupes de volumes   */
/*   = changement de volume */
proc,Fcl_type=LV

/*--------------------------------------------------------------------------*/
/*                                ROUTINES                                  */
/*                         par ordre alphabétique                           */
/*--------------------------------------------------------------------------*/

/* Liste des routines                                                       */


rout,Fcd2Fcl(§mat)
/*  Fcd2Fcl(§mat) Crée des FCL à partir d'un FCD en supprimant les          */
/*         doublons visibles dans le plan appliqué                          */
{
  if,"[§mat]:r><hbcFCD" /* vérification qu'il s'agit bien d'une coupe de lot */
  then
  {
    var,§err_msg
    §err_msg=¹Le composant [§mat] n'est pas une coupe de volume¹
    /* message à optimiser en utilisant le xxxx de hbcFCD"xxxx"=FCD */
    errm,mess={§err_msg},ouvr=1
  }
  else
  {
    var,§fcl
    
    dupl,[§mat],[hbcFCL]
    §fcl=[mm]
    ral,[§fcl]&R0:L=
    [§fcl]&Q0:
    [§fcl]&Q4:
    [§fcl]&V0:
    [§fcl]&V1:
    
    [§fcl]:MD=[Fcl_md] /* modèle par défaut */
    
    var,§dtc,§in,§io,§ir
    run,DateCourante(§dtc)
    §in="calculé"
    §io="[epUsr]" /* procédure définie dans [epInitDir]\ep_locales.txt */
    §ir="Issu de la coupe de volume : [[[§mat]&R0:L]&T2:nom] [[§mat]&V0:niv] [[§mat]&V0:ind] ([§mat])"
    run,SubStr(§ir,`  `,` `,§ir)
    
    run,EcritRal(§dtc,[§fcl],Q0,dtc,date)
    run,EcritRal(§in,[§fcl],Q0,in,txt)
    run,EcritRal(§io,[§fcl],Q0,io,txt)
    run,EcritRal(§ir,[§fcl],Q0,ir,txt)
    run,EcritRal(Fcl_type,[§fcl],V0,type,txt) /* la nouvelle limite est par défaut une limite de changement de volume */
    
    !EpFclTemp=0
    run,DcompLigne(§fcl,0,0,!EpFclTemp) /* décomposition en arc principaux, sans suppression des "petits arcs" */
    runs,!EpFclTemp
    {
      run,NormL(mm)
    }
    /* on supprime les "doublons" géométrique, i.e. les limites se trouvant     */
    /* sous une limite déjà existante au niveau du plan de travail              */
    if,"defprc(`jtMatPlan`)"
    {
      !EpCmpTemp=[hbcFCL]*!dom([[jtMatPlan]&D0:])+[[jtMatPlan]&R0:E]
      runs,!EpFclTemp
      {
        !EpFclTemp>[mm]
        doub,lign=[mm],sell=!EpCmpTemp,matc=[mm]
      }
      !sele,!EpCmpTemp
    }
    !sele,!EpFclTemp
  }
}