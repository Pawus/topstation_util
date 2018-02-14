/* version 0.1 du                                                           */
/*  dernière modification :                                                 */
/*         01 06 2015 (SD)                                                  */
/*  auteur :                                                                */
/*         SD Samuel Déom (sdeom@epadesa.fr)                                */


/* Pour fonctionner il faut inclure préalablement les boites à outils :     */
/*  epTypeOutils                                                            */
/*  epPlanOutils                                                            */
/*  epTexteOutils (pour epPlanOutils)                                       */

/* Procédures de l'environnement                                            */
proc,Fed_md=EP_ZON_EDDV

/* Liste des routines                                                       */
/*  AplPlan Applique le plan du même état descriptif de division en volumes */
/*           dont l'altitude est immédiatement supérieure ou inférieure à   */
/*           celle du plan actuellement tracé                               */
/*  DetFED(§prc_fed) Détermine le matricule correspondant à l'état descrip- */
/*           tif associé au plan qui est tracé                              */
/*  DetPlanInf(§prc_plan) Détermine le matricule correspondant au plan du   */
/*           même état descriptif de division en volumes dont l'altitude    */
/*           est immédiatement inférieur à celle du plan actuellement tracé */
/*  DetPlanSup(§prc_plan) Détermine le matricule correspondant au plan du   */
/*           même état descriptif de division en volumes dont l'altitude    */
/*           est immédiatement supérieur à celle du plan actuellement tracé */


/*--------------------------------------------------------------------------*/
/*                                ROUTINES                                  */
/*                         par ordre alphabétique                           */
/*--------------------------------------------------------------------------*/

rout,AplPlan(§type)
/*  Applique le plan du même état descriptif de division en volumes dont    */
/*           l'altitude est immédiatement inférieure ou supérieure à celle  */
/*           du plan actuellement tracé selon que §type vaut "Inf" ou "Sup" */
/*    S'il n'y a pas de plan répondant à ce critère, ne fait rien           */
/*  Dernière modification : 01 06 2015 (SD)                                 */
{
  var,§mat
  §mat=[EpTypeVide]
  if,"[§type==`Inf`]#[§type==`Sup`]"
  {
    run,DetPlanEdd([§type],§mat)
  }
  if,"§mat><EpTypeVide"
  {
    plna,[§mat]
  }
}

rout,DetFED(§prc_fed)
/* Détermine le matricule correspondant à l'état descriptif associé au plan */
/*           qui est tracé                                                  */
/*    L'indice en renvoyé dans la procédure dont le nom est indiqué dans    */
/*           §prc_fed                                                       */
/*  Dernière modification : 01 06 2015 (SD)                                 */
{
  var,§fed
  
  §fed=
  if,"defprc(`jtMatPlan`)"
  {
    §fed=[[jtMatPlan]&r0:E]
  }
  
  if,"§fed><``"
  {
    [§prc_fed]=[§fed]
  }
  else
  {
    [§prc_fed]=[EpTypeVide]
  }
}

rout,DetPlanEdd(§type,§prc_plan)
/*  Détermine le matricule correspondant au plan du même état descriptif de */
/*           division en volumes dont l'altitude est immédiatement inféri-  */
/*           eure ou supérieure à celle du plan actuellement tracé          */
/*    L'indice en renvoyé dans la procédure dont le nom est indiqué dans    */
/*           §prc_plan                                                      */
/*  Dernière modification : 01 06 2015 (SD)                                 */
{
  var,§fed,§test
  
  [§prc_plan]=[EpTypeVide]
  
  run,DetFED(§fed)
  if,"§fed><EpTypeVide"
  {
    §test=!test(&r0:e==[§fed])
    run,DetPlan([§type],§test,[§prc_plan])
  }
}

rout,TraPlan(§type)
/*  Applique le plan du même état descriptif de division en volumes dont    */
/*           l'altitude est immédiatement inférieure ou supérieure à celle  */
/*           du plan actuellement tracé selon que §type vaut "Inf" ou "Sup" */
/*           en conservant les paramètres de vue                            */
/*    S'il n'y a pas de plan répondant à ce critère, ne fait rien           */
/*  Dernière modification : 01 06 2015 (SD)                                 */
{
  var,§x,§y,§l,§h,§g,§ec
  var,§mat
  §mat=[EpTypeVide]
  
  §x=[xmvue]
  §y=[ymvue]
  §l=[2*dlvue]
  §h=[2*dhvue]
  §g=[%PLA:G]
  §ec=[%PLA:E]
  
  /* on simule une application de plan */
  if,"[§type==`Inf`]#[§type==`Sup`]"
  {
    run,DetPlanEdd([§type],§mat)
  }
  if,"§mat><EpTypeVide"
  {
    %PLA:X=[[§mat]:X]
    %PLA:Y=[[§mat]:Y]
    %PLA:L=[[§mat]:Cx]
    %PLA:H=[[§mat]:Cy]
    runr,comp=[§mat],type=K
    {
      [[rr]:][ex]
    }
    jtMatPlan=[§mat]
  }
  
  %PLA:G=[§g]
  %PLA:E=[§ec]
  cvue,x=[§x],y=[§y],l=[§l],h=[§h]
}