plugins {
    id("com.android.application")
    kotlin("android")
}

android {
    namespace = "com.arvinapp.pdfreader"
    compileSdk = 34

    defaultConfig {
        applicationId = "com.arvinapp.pdfreader"
        minSdk = 21
        targetSdk = 35
        versionCode = 6
        versionName = "4.3"
    }

    buildTypes {
        release {
            isMinifyEnabled = false
            proguardFiles(
                getDefaultProguardFile("proguard-android-optimize.txt"),
                "proguard-rules.pro"
            )
        }
    }

    compileOptions {
        sourceCompatibility = JavaVersion.VERSION_17
        targetCompatibility = JavaVersion.VERSION_17
    }

    kotlinOptions {
        jvmTarget = "17"
    }
}

dependencies {
    implementation("androidx.appcompat:appcompat:1.6.1")
    implementation("androidx.core:core-ktx:1.10.1")
    implementation("org.jetbrains.kotlin:kotlin-stdlib:1.8.22")
}
