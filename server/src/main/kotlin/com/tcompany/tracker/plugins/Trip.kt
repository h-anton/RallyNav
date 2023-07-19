package com.tcompany.tracker.plugins

import com.tcompany.tracker.format.gpx.GpxGpx
import io.ktor.http.*
import io.ktor.server.application.*
import io.ktor.server.request.*
import io.ktor.server.response.*
import io.ktor.server.routing.*

fun Application.configureTripHandling() {

    routing {
        accept(GPXContentType) {
            post("/trips") {
                val input = call.receive<GpxGpx>()
                print(input)

                call.respond(HttpStatusCode.OK, "")
            }
        }
    }
}