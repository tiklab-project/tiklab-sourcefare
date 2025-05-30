package io.tiklab.sourcefare.starter.annotation;

import io.tiklab.sourcefare.starter.config.SourceFareConfiguration;
import org.springframework.context.annotation.Import;

import java.lang.annotation.*;

@Target({ElementType.TYPE})
@Retention(RetentionPolicy.RUNTIME)
@Documented
@Import({SourceFareConfiguration.class })
public @interface EnableSourceFare {
}
