package io.tiklab.sourcefare;

import org.springframework.context.annotation.Import;

import java.lang.annotation.*;

@Target({ElementType.TYPE})
@Retention(RetentionPolicy.RUNTIME)
@Documented
@Import({SourceWairServerAutoConfiguration.class})
public @interface EnableSourceWairServer {
}
