---


---

<h1 id="temperatuur-en-vochtigheidsmeter">Temperatuur en vochtigheidsmeter</h1>
<p>Voor het keuzevak Project Data Science &amp; IoT was de opdracht om prototype te maken voor een Internet of Things (IoT) data-pijplijn scenario. Ook moest je bekend worden met Data Science concepten die werken met IoT applicatie door ze te maken.</p>
<h2 id="kiezen-van-een-iot-data-pijplijn-scenario">Kiezen van een IoT data-pijplijn scenario</h2>
<p>Bij het kiezen van een object is het belangrijk dat het idee dat klein is, concreet is en het moet makkelijk te implementeren zijn.<br>
Aangezien ik op het platteland woon zijn er veel kassen bij mij in de buurt. In deze kassen is temperatuur en vochtigheid heel belangrijk voor het groeien van planten. Kassen zijn echter meestal opgesplitst in verschillende segmenten. Ieder segment moet dus de mogelijkheid hebben om zijn eigen temperatuur en vochtigheid te kunnen regelen. Voor de eigenaar is het dus belangrijk om te kijken wat voor invloed de temperatuur en vochtigheid heeft gehad op zijn planten. Ik ben dus op het idee gekomen om een temperatuur en vochtigheidsmeter te maken die klein is en in ieder segment in de kas kan worden gehangen.</p>
<p>Het is belangrijk dat de eigenaar kan zien wat het verloop van de temperatuur en vochtigheid is geweest in de afgelopen tijd. Een mooi platform voor dit soort onderzoeken is <strong>ThingSpeak</strong>. Dit is een IoT platform waar data van sensoren naar toe kunnen worden gepost. Op ThingSpeak kan de eigenaar dus zijn temperatuur en vochtigheid zien van ieder segment (in mijn prototype is het er maar 1).</p>
<p>Verder moet er ook iets met de gemeten data gebeuren. Voor dit prototype heb ik er voor gekozen om de gemeten data op een OLED-scherm te laten zien. Zodat je niet steeds ThingSpeak erbij hoeft te pakken, maar in één oog opzicht gezien kan worden wat de status is van een segment van een kas.</p>
<h2 id="hoe-heb-ik-dit-gemaakt">Hoe heb ik dit gemaakt</h2>
<p>Ik heb een temperatuur en vochtigheidsmeter gemaakt en een apparaat om de gemeten temperatuur uit te lezen.</p>
<p><strong>De temperatuur en vochtigheidsmeter</strong><br>
Deze bestaat uit een Raspberry Pi Zero W, een DHT22 en een LED. Deze heb ik als volgt aangesloten.<br>
<img src="https://github.com/StevenSlaa/Project-Data-Science---IoT/blob/master/Raspberry%20Pi/Schematische%20Tekening%20Raspberry%20Pi%20Zero%20W%20-%20DHT22.png?raw=true" alt="Schematische Tekening Raspberry Pi Zero W - DHT22"><br>
De Raspberry PI haalt om de 6 seconde informatie (Dit is erg snel, voor temperatuur en vochtheid ophalen) op van de DHT22 dit gebeurt via OneWire-communcatie. De Raspberry PI stuurt deze data via een JSON-packet naar de ThingSpeak API. Dit gebeurt met POST requests.</p>
<p><strong>ThingSpeak</strong><br>
Bij Thingspeak heb ik een kanaal gemaakt met 2 velden.</p>
<ul>
<li>Field 1: Temperatuur</li>
<li>Field 2: Humidity</li>
</ul>
<p>Als we specifieke informatie willen opvragen kunnen we aan de ThingSpeak API vragen om een specifiek veld.<br>
<img src="https://github.com/StevenSlaa/Project-Data-Science---IoT/blob/master/Thingspeak/Thingspeak%20Channel%20Screenshot.png?raw=true" alt="Thingspeak kanaal screenshot"></p>
<p><strong>Temperatuur lezer</strong><br>
Om iets met de verzamelde data te doen, heb ik een ESP32 genomen (die verbonden is met WiFi) en deze gekoppeld aan een OLED display.<br>
<img src="https://github.com/StevenSlaa/Project-Data-Science---IoT/blob/master/Arduino/Schematische%20Tekening%20ESP32%20-%20%20I2C%20OLED.png?raw=true" alt="Schematische Tekening ESP32 - I2C OLED"></p>
<p>De ESP32 stuurt GET Requests naar de ThingSpeak API. Dit wordt gedaan met de Thingspeak Library. De ESP32 stuurt de opgehaalde data via I2C communicatie naar de OLED display.</p>
<h2 id="hoe-ziet-de-data-pijplijn-eruit">Hoe ziet de Data-pijplijn eruit?</h2>
<p>We beginnen bij de DHT22 deze genereert de data met behulp van sensoren. Deze verstuurd de data via het One-wire protocol door naar de Raspberry PI Zero W.</p>
<p>De Raspberry PI Zero W ontvangt de data van de DHT22 en zet het in een JSON-formaat. Deze JSON wordt verstuurd via een POST request naar de ThingSpeak API.</p>
<p>ThingSpeak maakt de informatie beschikbaar om overal te kunnen gebruiken. In mijn prototype wordt hier een ESP32 Gebruikt. Deze vraagt velden op aan de ThingSpeak API via GET Requests (wordt gebruik gemaakt van de ThingSpeak library, maar achter de schermen worden er GET Requests verstuurd naar de ThingSpeak API).</p>
<p>De ESP32 zet de data in een goed te lezen formaat en stuurt dit met het I2C protocol naar de OLED display. Dit kan de gebruiker weer aflezen. Natuurlijk kan er aan de ESP32 andere actuatoren worden gehangen (denk hierbij aan een relay), maar voor demonstratie redenen heb ik een OLED display genomen.</p>
<h2 id="conclusie">Conclusie</h2>
<p>Tijdens het ontwikkelen van deze codes had ik niet echt problemen ondervonden. De ThingSpeak API was goed onderbouwd. Het enige probleem is dat er een maximum aantal berichten is dat je per account kan versturen/ontvangen. Dit is niet handig op lange termijn.</p>
<p>Ik heb voor dit keuzevak nog nooit met een raspberry Pi of in python heb geprogrammeerd. Dit was dan ook de hoofdreden dat ik dit keuzevak heb gekozen. Ik vind dat mijn doel daarom ook zeker is bereikt. Ik heb in python leren programmeren en GPIO’s aangestuurd op een Raspberry Pi.</p>
<p>Als ik terug kijk op dit keuzevak heb ik geleerd om data stromen te analyseren en te kijken waar iets met deze data gebeurt. Zo kom je namelijk sneller achter problemen die ontstaan bij deze stromen. Bijvoorbeeld toen ik de DHT aansloot op de Raspberry pi bleek dit niet snel te werken. Er moest namelijk minimaal 6 seconden tussen de verzoeken zitten naar de sensor. Dit had ik in eerste instantie niet gezien en had daarom het probleem sensor geen waardes terug gaf toen ik daarom vroeg.</p>
<p>In de toekomst kunnen er aan de ESP32 andere actuatoren worden gehangen om de data stroom te verlengen. Denk hierbij aan een relay die een ventilator aanzet als de temperatuur boven een bepaalde grens komt.</p>
<h2 id="git-repository">Git repository</h2>
<p>Ik heb mijn repository opgedeeld in 3 mappen</p>
<ul>
<li><strong>Arduino</strong>: Hier in staan de schematische tekeningen en codes van ESP32 met de OLED Display de eind versie heet <code>Arduino-ThingSpeak</code>. Ik heb <code>Arduino_GET_OLED</code> gebruikt data (zonder de library) op te halen (dit werkt ook). <code>Arduino_I2C_Scanner</code> heb ik gebruikt om het I2C address te vinden van de OLED Display.</li>
<li><strong>Raspberry Pi</strong> Hierin staan verschillende codes voor het aansturen van een LED, het uitlezen van de DHT22 en het posten naar de Thingspeak API. De eindversie heet <code>dhtThingSpeak.py</code>.</li>
<li><strong>Thingspeak</strong> Hierin staat enkel en alleen een screenshot van hoe mijn kanaal eruit ziet met data erin.</li>
</ul>
<blockquote>
<p>Gemaakt door: Steven Slaa (0965538)<br>
Klas: TI2C</p>
</blockquote>

