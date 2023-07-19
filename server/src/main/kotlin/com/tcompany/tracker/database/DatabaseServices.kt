package com.tcompany.tracker.database

import io.ktor.server.application.*
import io.ktor.server.plugins.*
import io.ktor.util.*

class DatabaseServices private constructor(config: DatabaseServicesConfiguration) {
    companion object : BaseApplicationPlugin<Application, DatabaseServicesConfiguration, DatabaseServices> {
        override val key: AttributeKey<DatabaseServices> = AttributeKey("DatabaseServices")

        override fun install(
            pipeline: Application,
            configure: DatabaseServicesConfiguration.() -> Unit
        ): DatabaseServices = DatabaseServices(DatabaseServicesConfiguration().apply(configure))
    }
    private val map = config.map

    fun getDatabase(clazz: Class<out Service>): Service? = map[clazz]

    inline fun <reified T: Service> database(): T = (getDatabase(T::class.java) ?: throw NotFoundException("${T::class.java} not found!")) as T

    class DatabaseServicesConfiguration {
        internal val map = HashMap<Class<out Service>, Service>()

        fun <T: Service> add(clazz: Class<T>, service: T): T {
            map[clazz] = service
            return service
        }

        inline fun <reified T: Service> add(service: T): T = add(T::class.java, service)
    }
}

inline fun <reified T: Service> Application.database(): T = plugin(DatabaseServices).database<T>()