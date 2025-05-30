package io.tiklab.sourcefare.starter;


import io.tiklab.core.property.PropertyAndYamlSourceFactory;
import io.tiklab.sourcefare.starter.annotation.EnableSourceFare;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.boot.web.servlet.ServletComponentScan;
import org.springframework.context.annotation.PropertySource;
import org.springframework.scheduling.annotation.EnableScheduling;

@SpringBootApplication
@EnableScheduling
@PropertySource(value = {"classpath:application.yaml"}, factory = PropertyAndYamlSourceFactory.class)
@EnableSourceFare
@ServletComponentScan("io.tiklab.sourcewair")
public class SourceFareApplication {

	public static void main(String[] args) {

		SpringApplication.run(SourceFareApplication.class, args);
	}

}
