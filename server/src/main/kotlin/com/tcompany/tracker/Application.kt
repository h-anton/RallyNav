package com.tcompany.tracker

import io.ktor.server.application.*
import io.ktor.server.engine.*
import io.ktor.server.netty.*
import com.tcompany.tracker.plugins.*

fun main() {
    val env = applicationEngineEnvironment {
        module {
            module()
        }

        val myPort = config.propertyOrNull("ktor.deployment.port")?.getString()?.toInt()

        connector {
            host = "0.0.0.0"
            port = myPort ?: 3000
        }

        developmentMode = true
    }
    embeddedServer(Netty, env).start(wait = true)
}

fun Application.module() {
    configureSecurity()
    configureSerialization()

    configureDatabases()
    configureLogin()

    configureSockets()
    configureTripHandling()
}
