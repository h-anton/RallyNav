package com.tcompany.tracker.plugins

import com.auth0.jwt.interfaces.Payload
import com.tcompany.tracker.JWTHelper.configureJWT
import io.ktor.http.*
import io.ktor.server.application.*
import io.ktor.server.auth.*
import io.ktor.server.auth.jwt.*
import io.ktor.server.plugins.cors.routing.*
import io.ktor.server.response.*
import io.ktor.server.sessions.*
import kotlin.collections.set

data class HttpsSession(
    val jwtHeader: String,
    val jwtPayload: String
)

data class HttpOnlySession(
    val jwtSignature: String
)

fun Application.configureSecurity() {
    install(CORS) {
        allowHeader(HttpHeaders.ContentType)
        allowCredentials = true
        allowHost("localhost:3000")
    }

    authentication {
        configureJWT()
    }


    install(Sessions) {
        cookie<HttpOnlySession>("HTTP_ONLY_SESSION") {
            //cookie.extensions["SameSite"] = "none" // make this secure later
            cookie.httpOnly = true
            cookie.secure = !this@configureSecurity.developmentMode
        }

        cookie<HttpsSession>("SITE_SESSION") {
            //cookie.extensions["SameSite"] = "none"
            cookie.httpOnly = false
            cookie.secure = !this@configureSecurity.developmentMode
        }
    }
}

//If any of the permission are satisfied, then the user is authorized
suspend fun ApplicationCall.checkPermission(vararg perms: String) {
    val principal = principal<JWTPrincipal>() ?: throw Exception("No principal found")
    val permissions = principal.payload.getClaim("permissions").asList(String::class.java)

    for (perm in perms) {
        for (p in permissions) {
            if (p == "*") {
                return
            }

            // ex. has permission clients, ask for permission clients.read
            // is valid because clients.read starts with clients and the rest starts with . or
            //   is empty (so exactly the same)
            if (perm.startsWith(p)) {
                val rest = perm.substring(p.length);
                if (rest == "" || rest.startsWith(".")) {
                    return
                }
            }
        }
    }

    respond(HttpStatusCode.Forbidden)
    throw IllegalAccessException("No permission")
}
