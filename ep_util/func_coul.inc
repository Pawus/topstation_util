/* version 0.9 du 30 12 2009                                     */


/* nécessite l'ouverture préalable du lien odbc Registre Foncier */
/* et sa fermeture au retour de la fonction                      */
rout,GetCoul(§nompp)
{
  var,§select,§from,§where
  
  §select=Personne_Morale.Couleur AS COUL
  §from=Personne_Morale
  §where=Personne_Morale.Nom='[§nompp]'
  
  odbc,cmd=`SELECT {§select} FROM {§from} WHERE {§where}`,PREF="DB_"
  {
    runf,[epFicCoul],FORM=`NC;NR;CODECOUL`
    {
	  if,"DB_COUL==`[NC]`"
      {
        EpTeinte=[NR]
      }
    }
  }
}