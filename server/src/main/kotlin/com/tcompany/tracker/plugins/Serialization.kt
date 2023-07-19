package com.tcompany.tracker.plugins

import io.ktor.http.*
import io.ktor.serialization.*
import io.ktor.serialization.kotlinx.*
import io.ktor.serialization.kotlinx.json.*
import io.ktor.server.plugins.contentnegotiation.*
import io.ktor.server.response.*
import io.ktor.server.application.*
import io.ktor.server.routing.*
import nl.adaptivity.xmlutil.serialization.XML

val GPXContentType = ContentType("application", "gpx+xml")

fun Application.configureSerialization() {
    install(ContentNegotiation) {
        json()
        register(GPXContentType, KotlinxSerializationConverter(XML()))
    }
}


