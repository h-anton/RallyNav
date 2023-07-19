package com.tcompany.tracker.format.gpx

import kotlinx.datetime.Instant
import kotlinx.serialization.SerialName
import kotlinx.serialization.Serializable
import nl.adaptivity.xmlutil.serialization.XML
import nl.adaptivity.xmlutil.serialization.XmlElement
import nl.adaptivity.xmlutil.serialization.XmlSerialName

private val xml = XML()
fun parseGpx(xmlText: String): GpxGpx = xml.decodeFromString(GpxGpx.serializer(), xmlText)

@Serializable
@XmlSerialName("gpx", "http://www.topografix.com/GPX/1/0")
data class GpxGpx(
    //Properties
    val version: String,
    val creator: String,

    //Elements
    val waypoints: List<GpxWpt>,
    val tracks: List<GpxTrk>,
    val routes: List<GpxRte>,
    val bounds: GpxBounds?,

    @XmlElement val name: String?,
    @XmlElement val email: String?,
    @XmlElement val author: String?,
    @XmlElement val url: String?,
    @XmlElement val urlname: String?,
    @XmlElement val time: Instant?,
    @XmlElement val keywords: String?,
)

@Serializable
@XmlSerialName("wpt")
data class GpxWpt(
    //Properties
    val lat: Double,
    val lon: Double,

    //Elements
    @XmlSerialName("ele")
    @XmlElement val elevation: Double?,
    @XmlElement val time: Instant?,
    @XmlElement val magvar: Double?,
    @XmlElement val geoidheight: Double?,

    @XmlElement val name: String?,
    @XmlSerialName("cmt")
    @XmlElement val comment: String?,
    @XmlElement val desc: String?,
    @XmlElement val src: String?,
    @XmlElement val url: String?,
    @XmlElement val urlname: String?,
    @XmlElement val sym: String?,
    @XmlElement val type: String?,

    @XmlElement val fix: GpxFix?,
    @XmlElement val sat: Int?,
    @XmlElement val hdop: Double?,
    @XmlElement val vdop: Double?,
    @XmlElement val pdop: Double?,
    @XmlElement val ageofdgpsdata: Double?,
    @XmlElement val dgpsid: Int?,
)

@Serializable
@XmlSerialName("rte")
data class GpxRte(
    @XmlElement val name: String?,
    @XmlSerialName("cmt")
    @XmlElement val comment: String?,
    @XmlElement val desc: String?,
    @XmlElement val src: String?,
    @XmlElement val url: String?,
    @XmlElement val urlname: String?,
    @XmlElement val number: Int?,

    //TODO add rtept
)

@Serializable
@XmlSerialName("trk")
data class GpxTrk(
    @XmlElement val name: String?,
    @XmlSerialName("cmt")
    @XmlElement val comment: String?,
    @XmlElement val desc: String?,
    @XmlElement val src: String?,
    @XmlElement val url: String?,
    @XmlElement val urlname: String?,
    @XmlElement val number: Int?,

    val segments: List<GpxTrkSeg>,
)

@Serializable
@XmlSerialName("trkseg")
data class GpxTrkSeg(
    val points: List<GpxTrkPt>,
)

@Serializable
@XmlSerialName("trkpt")
data class GpxTrkPt(
    //Properties
    val lat: Double,
    val lon: Double,

    //Elements
    @XmlSerialName("ele")
    @XmlElement val elevation: Double?,
    @XmlElement val time: Instant?,
    @XmlElement val course: Double?,
    @XmlElement val speed: Double?,
    @XmlElement val magvar: Double?,
    @XmlElement val geoidheight: Double?,

    @XmlElement val name: String?,
    @XmlSerialName("cmt")
    @XmlElement val comment: String?,
    @XmlElement val desc: String?,
    @XmlElement val src: String?,
    @XmlElement val url: String?,
    @XmlElement val urlname: String?,
    @XmlElement val sym: String?,
    @XmlElement val type: String?,

    @XmlElement val fix: GpxFix?,
    @XmlElement val sat: Int?,
    @XmlElement val hdop: Double?,
    @XmlElement val vdop: Double?,
    @XmlElement val pdop: Double?,
    @XmlElement val ageofdgpsdata: Double?,
    @XmlElement val dgpsid: Int?,
)


@Serializable
@XmlSerialName("bounds")
data class GpxBounds(
    val minlat: Double,
    val minlon: Double,
    val maxlat: Double,
    val maxlon: Double,
)

@Serializable
enum class GpxFix {
    @SerialName("none") NONE,
    @SerialName("2d") TWO_D,
    @SerialName("3d") THREE_D,
    @SerialName("dgps") D_GPS,
    @SerialName("pps") PPS,
}

