nl.sp.drupal-spcivisync
=======================

Deze module haalt gebruikersgegevens uit CiviCRM op, en synced deze met lokale velden en rollen van Drupal gebruikers. Welke informatie er precies uit CiviCRM wordt opgehaald, en waar deze in Drupal terecht komt, is in te stellen met regels.

Een overzicht van de ingestelde regels is te vinden op het volgende pad: admin/config/sp/spcivisync.

Hier zijn ook de volgende typen regels toe te voegen (middels verschillende tabjes):

CiviCRM contact groep -> Drupal gebruiker rol
CiviCRM contact relatie -> Drupal gebruiker rol
CiviCRM contact veld -> Drupal gebruiker account veld
CiviCRM relatie -> Drupal gebruiker account veld

Tevens kan getest worden of een regel werkt met het tabje 'Test regels'. Selecteer een Drupal gebruiker, en klik op tekst. Je krijgt nu te zien wat er wordt gedaan. Als dit naar wens is kan je ook de wijzigingen echt op slaan. Zet daarvoor een vinkje in het vakje 'Wijzigingen opslaan in database'.

Tot slot voegt de module ook een tweetal acties voor de regels module toe. Namelijk: "Synchronizeer lokale gebruikersdata met CiviCRM voor één gebruiker" en "Synchronizeer lokale gebruikersdata met CiviCRM voor àlle gebruikers".

Wil je dat de gebruikersdata wordt gesynced op het moment dat iemand inlogt, voeg dan een regel toe met als trigger 'Gebruiker logt in' en als actie 'Sync local user data with civicrm data.'.
