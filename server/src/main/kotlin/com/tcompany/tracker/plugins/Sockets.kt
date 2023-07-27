package com.tcompany.tracker.plugins

import com.tcompany.tracker.standardRouting
import io.ktor.network.selector.*
import io.ktor.network.sockets.*
import io.ktor.server.websocket.*
import io.ktor.websocket.*
import java.time.Duration
import io.ktor.server.application.*
import io.ktor.server.routing.*
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.launch

fun Application.configureSockets() {
    install(WebSockets) {
        pingPeriod = Duration.ofSeconds(15)
        timeout = Duration.ofSeconds(15)
        maxFrameSize = Long.MAX_VALUE
        masking = false
    }

    standardRouting {
        webSocket("/ws") { // websocketSession
            for (frame in incoming) {
                if (frame is Frame.Text) {
                    val text = frame.readText()
                    outgoing.send(Frame.Text("YOU SAID: $text"))
                    if (text.equals("bye", ignoreCase = true)) {
                        close(CloseReason(CloseReason.Codes.NORMAL, "Client said BYE"))
                    }
                }
            }
        }
    }

    val socket = aSocket(SelectorManager(Dispatchers.IO)).udp().bind(InetSocketAddress(
        this.environment.config.host,
        this.environment.config.config("ktor.deployment")
            .propertyOrNull("udpPort")?.getString()?.toInt() ?: 2980
    ))

    repeat(this.environment.config.config("ktor.deployment")
        .propertyOrNull("udpProcessors")?.getString()?.toInt() ?: 2) {
        val channel = socket.incoming
        launch {
            for (datagram in channel) {
                //TODO process datagram
            }
        }
    }
}
