package com.tcompany.tracker

import io.ktor.http.*
import io.ktor.server.application.*
import io.ktor.server.routing.*

fun Application.standardRouting(block: Route.() -> Unit) {
    routing {
        accept(ContentType.Application.Json) {
            block()
        }
    }
}