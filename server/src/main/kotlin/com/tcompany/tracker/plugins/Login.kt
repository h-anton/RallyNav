package com.tcompany.tracker.plugins

import com.tcompany.tracker.JWTHelper
import com.tcompany.tracker.database.database
import com.tcompany.tracker.schemas.RentService
import com.tcompany.tracker.setupCookieJWT
import com.tcompany.tracker.standardRouting
import io.ktor.http.*
import io.ktor.server.application.*
import io.ktor.server.request.*
import io.ktor.server.response.*
import io.ktor.server.routing.*
import kotlinx.datetime.Clock
import kotlinx.datetime.toJavaInstant
import kotlinx.serialization.Serializable

@Serializable
data class TokenLogin(
    val token: String,
    val wantsToken: Boolean = false
)

fun Application.configureLogin() {
    val rentService = database<RentService>()

    standardRouting {
        post("/tlogin") {
            val login = call.receive<TokenLogin>()

            val rent = rentService.findByToken(login.token) ?: run {
                call.respond(HttpStatusCode.NotFound, "Invalid Token")
                return@post
            }

            if (rent.end < Clock.System.now()) {
                call.respond(HttpStatusCode.Forbidden, "Token expired")
                return@post
            }

            if (rent.start > Clock.System.now()) {
                call.respond(HttpStatusCode.Forbidden, "Token not yet valid")
                return@post
            }

            val token = JWTHelper.build {
                withClaim("rent", rent.id)
                withClaim("permissions", listOf("*")) // TODO add permissions
                withExpiresAt(rent.end.toJavaInstant())
            }

            if (login.wantsToken) {
                call.respond(HttpStatusCode.OK, token)
            } else {
                call.setupCookieJWT(token)
                call.respond(HttpStatusCode.OK, "")
            }
        }
    }
}