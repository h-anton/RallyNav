package com.tcompany.tracker

import com.auth0.jwt.JWT
import com.auth0.jwt.JWTCreator
import com.auth0.jwt.algorithms.Algorithm
import com.tcompany.tracker.plugins.HttpOnlySession
import com.tcompany.tracker.plugins.HttpsSession
import io.ktor.http.*
import io.ktor.http.auth.*
import io.ktor.server.application.*
import io.ktor.server.auth.*
import io.ktor.server.auth.jwt.*
import io.ktor.server.response.*
import io.ktor.server.sessions.*

object JWTHelper {
    private val jwtSecret = "secret"
    private val jwtAudience = "jwt-audience"
    private val jwtDomain = "https://jwt-provider-domain/"
    private val jwtRealm = "ktor sample app"

    fun build(builder: JWTCreator.Builder.() -> Unit): JWTToken =
        jwtOfString(JWT.create()
                .withAudience(jwtAudience)
                .withIssuer(jwtDomain)
                .apply(builder)
                .sign(Algorithm.HMAC256(jwtSecret)))

    fun AuthenticationConfig.configureJWT() {
        jwt {
            realm = jwtRealm
            authHeader {
                val header = it.request.parseAuthorizationHeader()
                if (header != null) return@authHeader header

                val session1 = it.sessions.get<HttpOnlySession>()
                val session2 = it.sessions.get<HttpsSession>()

                HttpAuthHeader.Single(
                    "Bearer",
                    "${session2?.jwtHeader}.${session2?.jwtPayload}.${session1?.jwtSignature}"
                )
            }

            verifier(
                    JWT
                            .require(Algorithm.HMAC256(jwtSecret))
                            .withAudience(jwtAudience)
                            .withIssuer(jwtDomain)
                            .build()
            )

            validate { credential ->
                var valid = credential.payload.audience.contains(jwtAudience)

                if (valid)
                    valid = credential.payload.getClaim("rent").asInt() > 0

                if (valid)
                    JWTPrincipal(credential.payload)
                else
                    null
            }

            challenge { defaultScheme, realm ->
                call.respond(HttpStatusCode.Unauthorized, "Token is not valid or has expired")
            }
        }
    }

    private fun jwtOfString(token: String): JWTToken {
        val parts = token.split(".")
        return JWTToken(parts[0], parts[1], parts[2])
    }
}

fun ApplicationCall.setupCookieJWT(token: JWTToken) {
    sessions.set(HttpOnlySession(token.signature))
    sessions.set(HttpsSession(token.header, token.payload))
}

data class JWTToken(val header: String, val payload: String, val signature: String)