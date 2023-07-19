package com.tcompany.tracker.schemas

import com.tcompany.tracker.Identified
import com.tcompany.tracker.database.LazyDB
import com.tcompany.tracker.database.SimpleServiceHelper
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.withContext
import kotlinx.datetime.Instant
import kotlinx.datetime.toJavaInstant
import kotlinx.datetime.toKotlinInstant
import kotlinx.serialization.Serializable
import java.sql.*
import kotlin.time.Duration

@Serializable
data class Rent(
    override val id: Int? = null,
    val client: LazyDB<Client>,
    val token: String, // for every rent we will provide a token to the client
    val start: Instant,
    val end: Instant
): Identified {
    val duration: Duration get() = end - start
}

class RentService(connection: Connection, private val clientService: ClientService): SimpleServiceHelper<Rent>(
    connection,
    "CREATE TABLE rent (" +
            "id SERIAL PRIMARY KEY," +
            "client SERIAL REFERENCES client(id)," +
            "token CHAR(10)," +
            "_start TIMESTAMP," +
            "_end TIMESTAMP" +
    ");",
    "SELECT client, token, _start, _end FROM rent WHERE id = ?;",
    "INSERT INTO rent (client, token, _start, _end) VALUES (?, ?, ?, ?);",
    "UPDATE rent SET client = ?, token = ?, _start = ?, _end = ? WHERE id = ?;",
    "DELETE FROM rent WHERE id = ?;"
) {

    suspend fun findByToken(token: String): Rent? = withContext(Dispatchers.IO) {
        val statement = connection.prepareStatement("SELECT id, client, token, _start, _end FROM rent WHERE token = ?;")
        statement.setString(1, token)
        val result = statement.executeQuery()

        if (result.next()) read(result.getInt("id"), result) else null
    }

    override suspend fun write(statement: PreparedStatement, rent: Rent) {
        statement.setInt(1, rent.client.id ?: clientService.create(rent.client.value()))
        statement.setString(2, rent.token)
        statement.setTimestamp(3, Timestamp.from(rent.start.toJavaInstant()))
        statement.setTimestamp(4, Timestamp.from(rent.end.toJavaInstant()))
    }

    override suspend fun read(id: Int, result: ResultSet): Rent = Rent(
        id,
        clientService.asLazy(result.getInt("client")),
        result.getString("token"),
        result.getTimestamp("_start").toInstant().toKotlinInstant(),
        result.getTimestamp("_end").toInstant().toKotlinInstant()
    )
}