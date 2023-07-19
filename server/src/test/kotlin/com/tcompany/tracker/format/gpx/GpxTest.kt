package com.tcompany.tracker.format.gpx

import io.kotest.core.spec.style.StringSpec
import io.kotest.matchers.shouldBe
import kotlinx.serialization.modules.SerializersModule
import nl.adaptivity.xmlutil.XmlDeclMode
import nl.adaptivity.xmlutil.serialization.XML

class GpxTest : StringSpec({
    "basic gpx parsing" {
        val text = """<?xml version="1.0" encoding="UTF-8"?>
<gpx xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" version="1.0" creator="RoadTracer"
     xmlns="http://www.topografix.com/GPX/1/0"
     xsi:schemaLocation="https://www.topografix.com/GPX/1/0/gpx.xsd">
    <bounds minlat="48.842575499" minlon="7.394539100" maxlat="49.360788995" maxlon="10.487678631"/>
    <wpt lat="49.245191139" lon="7.394539100">
        <name>001</name>
        <cmt></cmt>
    </wpt>
    <wpt lat="49.275854206" lon="8.693811835">
        <name>029</name>
        <cmt>Onder de brug doorrijden.</cmt>
    </wpt>
    <wpt lat="49.237675583" lon="8.771107698">
        <name>030</name>
        <cmt>op rondpunt eerste afslag&#13;
            de L292 oprjiden richting oostringen&#13;
        </cmt>
    </wpt>
    <wpt lat="49.233872235" lon="8.773564645">
        <name>031</name>
        <cmt>2de afrit op rondpunt&#13;
            De Schlossstrase nemen&#13;
            &#13;
        </cmt>
    </wpt>
    <trk>
        <name>dinsdag 24 mei</name>
    </trk>
</gpx>"""

        val xml = XML()
        val gpx = xml.decodeFromString(GpxGpx.serializer(), text)
        
        gpx.waypoints.size shouldBe 4
        gpx.waypoints[0].name shouldBe "001"
        gpx.waypoints[0].comment shouldBe ""
        gpx.waypoints[1].name shouldBe "029"
        gpx.waypoints[1].comment shouldBe "Onder de brug doorrijden."

        gpx.tracks.size shouldBe 1
        gpx.tracks[0].name shouldBe "dinsdag 24 mei"
    }

    "full file parse" {
        val text = this::class.java.getResource("/example.gpx").readText()
        val xml = XML()
        val gpx = xml.decodeFromString(GpxGpx.serializer(), text)

        gpx.bounds?.minlat shouldBe 48.842575499
        gpx.bounds?.minlon shouldBe 7.394539100
        gpx.bounds?.maxlat shouldBe 49.360788995
        gpx.bounds?.maxlon shouldBe 10.487678631
    }
})
