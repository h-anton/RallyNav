package com.tcompany.tracker.plugins

import com.tcompany.tracker.database.DatabaseServices
import com.tcompany.tracker.database.database
import com.tcompany.tracker.schemas.ClientService
import com.tcompany.tracker.schemas.RentService
import com.tcompany.tracker.database.SimpleService
import com.tcompany.tracker.schemas.Client
import com.tcompany.tracker.schemas.Rent
import com.tcompany.tracker.standardRouting
import io.ktor.http.*
import io.ktor.server.request.*
import io.ktor.server.response.*
import kotlinx.coroutines.*
import java.sql.*
import io.ktor.server.application.*
import io.ktor.server.auth.*
import io.ktor.server.auth.jwt.*
import io.ktor.server.plugins.*
import io.ktor.server.routing.*
import kotlinx.datetime.Clock
import kotlinx.datetime.Instant
import org.postgresql.gss.MakeGSS.authenticate

fun Application.configureDatabases() {

    val dbConnection: Connection = connectToPostgres(developmentMode)

    install(DatabaseServices) {
        val clientService = add(ClientService(dbConnection))
        val rentService = add(RentService(dbConnection, clientService))
    }

    if (developmentMode) {
        val clientService = database<ClientService>()
        val rentService = database<RentService>()

        runBlocking {
            val clientId = clientService.create(Client(
                null,
                "Admin",
                "admin@admin.org",
                "+066606660",
                "Admin Street",
                "Nowhere",
                "Somewhere",
                "666"))

            rentService.create(
                Rent(
                    null,
                    clientService.asLazy(clientId),
                    "admin",
                    Clock.System.now(),
                    Instant.DISTANT_FUTURE
                )
            )
        }
    }

    standardRouting {
        authenticate {
            configureServiceRouting("clients", this@configureDatabases.database<ClientService>())
            configureServiceRouting("rents", this@configureDatabases.database<RentService>())
        }
    }
}

/**
 * Makes a connection to a Postgres database.
 *
 * In order to connect to your running Postgres process,
 * please specify the following parameters in your configuration file:
 * - postgres.url -- Url of your running database process.
 * - postgres.user -- Username for database connection
 * - postgres.password -- Password for database connection
 *
 * If you don't have a database process running yet, you may need to [download]((https://www.postgresql.org/download/))
 * and install Postgres and follow the instructions [here](https://postgresapp.com/).
 * Then, you would be able to edit your url,  which is usually "jdbc:postgresql://host:port/database", as well as
 * user and password values.
 *
 *
 * @param embedded -- if [true] defaults to an embedded database for tests that runs locally in the same process.
 * In this case you don't have to provide any parameters in configuration file, and you don't have to run a process.
 *
 * @return [Connection] that represent connection to the database. Please, don't forget to close this connection when
 * your application shuts down by calling [Connection.close]
 * */
fun Application.connectToPostgres(embedded: Boolean): Connection {
    Class.forName("org.postgresql.Driver")
    if (embedded) {
        return DriverManager.getConnection("jdbc:h2:mem:test;DB_CLOSE_DELAY=-1", "root", "")
    } else if (environment.developmentMode) {
        return DriverManager.getConnection("jdbc:postgresql://localhost:5432/tracker", "postgres", "bannana")
    } else {
        val url = environment.config.property("postgres.url").getString()
        val user = environment.config.property("postgres.user").getString()
        val password = environment.config.property("postgres.password").getString()

        return DriverManager.getConnection(url, user, password)
    }
}

// Makes a generic CRUD routing for a given service.
inline fun <reified T: Any> Route.configureServiceRouting(name: String, service: SimpleService<T>) {
    post("/${name}") {
        call.checkPermission("${name}.create")

        val city = call.receive<T>()
        val id = service.create(city)
        call.respond(HttpStatusCode.Created, id)
    }

    get("/${name}/{id}") {
        call.checkPermission("${name}.read")

        val id = call.parameters["id"]?.toInt() ?: throw IllegalArgumentException("Invalid ID")
        try {
            val value = service.read(id)
            call.respond(HttpStatusCode.OK, value)
        } catch (e: NotFoundException) {
            call.respond(HttpStatusCode.NotFound)
        }
    }

    put("/${name}/{id}") {
        call.checkPermission("${name}.update")

        val id = call.parameters["id"]?.toInt() ?: throw IllegalArgumentException("Invalid ID")
        val value = call.receive<T>()
        service.update(id, value)
        call.respond(HttpStatusCode.OK)
    }

    delete("/${name}/{id}") {
        call.checkPermission("${name}.delete")

        val id = call.parameters["id"]?.toInt() ?: throw IllegalArgumentException("Invalid ID")
        service.delete(id)
        call.respond(HttpStatusCode.OK)
    }
}

